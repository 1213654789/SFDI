#include "timerthread.h"
#include <chrono>
#include <thread>
#include <QCoreApplication>
#include <QMetaObject>

TimerThread::TimerThread(unsigned int interval_us, std::function<void()> cb)
    : m_running(false), m_interval_us(interval_us), m_callback(std::move(cb))
{
}

TimerThread::~TimerThread()
{
    stop();
}

void TimerThread::start()
{
    if (m_running.load()) return;
    m_running.store(true);
    m_thread = std::thread(&TimerThread::runLoop, this);
}

void TimerThread::stop()
{
    m_running.store(false);
    if (m_thread.joinable()) m_thread.join();
}

void TimerThread::runLoop()
{
    using namespace std::chrono;

    while (m_running.load()) {
        auto start = steady_clock::now();

        if (m_interval_us > 200) {
            std::this_thread::sleep_for(microseconds(m_interval_us - 200));
        }

        while (m_running.load() && duration_cast<microseconds>(steady_clock::now() - start).count() < (long long)m_interval_us) {
            std::this_thread::yield();
        }

        if (!m_running.load()) break;

        // If a callback is provided, invoke it in the Qt main loop thread using a queued connection
        if (m_callback && QCoreApplication::instance()) {
            // copy the callback to ensure it's safe to modify m_callback elsewhere
            auto cb = m_callback;
            QMetaObject::invokeMethod(QCoreApplication::instance(), cb, Qt::QueuedConnection);
        }
    }
}

void TimerThread::setCallback(std::function<void()> cb)
{
    m_callback = std::move(cb);
}
