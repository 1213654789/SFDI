#include "timerthread.h"

#include "timerthread.h"
#include <chrono>
#include <thread>
#include <QCoreApplication>
#include <QMetaObject>
#include <QDebug>
#include <cmath>

using namespace std::chrono;

TimerThread::TimerThread(unsigned int interval_us, std::function<void()> cb, bool invokeInMainThread, unsigned int busy_wait_us, int64_t repeatCount)
    : m_running(false), m_paused(false), m_interval_us(interval_us), m_busy_wait_us(busy_wait_us), m_invoke_main(invokeInMainThread), m_repeatCount(repeatCount), m_callback(std::move(cb))
{
}

TimerThread::~TimerThread()
{
    stop();
}

void TimerThread::start()
{
    bool expected = false;
    if (!m_running.compare_exchange_strong(expected, true)) return; // already running

    m_paused.store(false);
    m_thread = std::thread(&TimerThread::runLoop, this);
}

void TimerThread::stop()
{
    m_running.store(false);
    m_paused.store(false);
    m_cv.notify_all();
    if (m_thread.joinable()) m_thread.join();
}

void TimerThread::pause()
{
    if (!m_running.load()) return;
    m_paused.store(true);
}

void TimerThread::resume()
{
    if (!m_running.load()) return;
    m_paused.store(false);
    m_cv.notify_all();
}

void TimerThread::setCallback(std::function<void()> cb)
{
    std::lock_guard<std::mutex> lk(m_mutex);
    m_callback = std::move(cb);
}

void TimerThread::setRepeatCount(int64_t repeatCount)
{
    m_repeatCount = repeatCount;
}

void TimerThread::runLoop()
{
    // Scheduling uses steady_clock for monotonic timing
    steady_clock::time_point start_time = steady_clock::now();
    steady_clock::duration interval = microseconds(static_cast<long long>(m_interval_us));

    int64_t tick = 0;

    while (m_running.load()) {
        // handle pause
        if (m_paused.load()) {
            std::unique_lock<std::mutex> lk(m_mutex);
            m_cv.wait(lk, [this]{ return !m_paused.load() || !m_running.load(); });
            if (!m_running.load()) break;
            // adjust start_time so that drift compensation continues from now
            start_time = steady_clock::now() - interval * tick;
        }

        // compute next expected tick time (drift-compensated)
        ++tick;
        steady_clock::time_point next_time = start_time + interval * tick;

        // sleep until next_time - busy_wait
        steady_clock::time_point busy_start = next_time - microseconds(m_busy_wait_us);
        auto now = steady_clock::now();
        if (now < busy_start) {
            // sleep most of the time using sleep_until, but wake earlier on stop/pause
            std::unique_lock<std::mutex> lk(m_mutex);
            m_cv.wait_until(lk, busy_start, [this]{ return !m_running.load() || m_paused.load(); });
            if (!m_running.load()) break;
            if (m_paused.load()) continue; // loop will handle pause
        }

        // busy-wait remainder for higher precision
        while (m_running.load() && steady_clock::now() < next_time) {
            std::this_thread::yield();
        }

        if (!m_running.load()) break;

        // invoke callback (either in main thread via queued invoke, or directly)
        std::function<void()> cb_copy;
        {
            std::lock_guard<std::mutex> lk(m_mutex);
            cb_copy = m_callback;
        }

        if (cb_copy) {
            if (m_invoke_main && QCoreApplication::instance()) {
                // Wrap the callback to catch any exceptions thrown in the main thread
                auto safe_cb = [cb_copy]() {
                    try {
                        cb_copy();
                    } catch (const std::exception &ex) {
                        qDebug() << "TimerThread: exception in callback (main thread):" << ex.what();
                    } catch (...) {
                        qDebug() << "TimerThread: unknown exception in callback (main thread)";
                    }
                };
                QMetaObject::invokeMethod(QCoreApplication::instance(), safe_cb, Qt::QueuedConnection);
            } else {
                try {
                    cb_copy();
                } catch (const std::exception &ex) {
                    qDebug() << "TimerThread: exception in callback (worker thread):" << ex.what();
                } catch (...) {
                    qDebug() << "TimerThread: unknown exception in callback (worker thread)";
                }
            }
        }

        // check repeat count (tick is 1-based)
        if (m_repeatCount >= 0 && tick >= m_repeatCount) {
            // finished
            m_running.store(false);
            break;
        }
    }
}

