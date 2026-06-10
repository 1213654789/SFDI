#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H


#include <atomic>
#include <functional>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <cstdint>

// High-precision timer based on std::thread.
// Features:
// - microsecond interval
// - drift compensation (schedule based on steady_clock start + n*interval)
// - minimal busy-wait (configurable busy_wait_us)
// - pause / resume / stop
// - optional invoke callback in Qt main thread (queued)
// - optional repeat count (negative = infinite)
class TimerThread
{
public:
    // interval_us: interval in microseconds
    // cb: callback invoked on each tick
    // invokeInMainThread: if true, callback is invoked in Qt main thread via queued connection
    // busy_wait_us: final busy-wait window in microseconds to improve precision (default small value)
    // repeatCount: number of total callbacks to run; -1 for infinite
    // Default interval reduced to 100 us (0.1 ms) for higher resolution.
    // Default busy_wait_us reduced to 50 us to allow finer final spin-wait window.
    explicit TimerThread(unsigned int interval_us = 100,
                         std::function<void()> cb = nullptr,
                         bool invokeInMainThread = true,
                         unsigned int busy_wait_us = 50,
                         int64_t repeatCount = -1);

    ~TimerThread();

    void start();
    void stop();
    void pause();
    void resume();

    void setCallback(std::function<void()> cb);
    void setRepeatCount(int64_t repeatCount);
    bool isRunning() const { return m_running.load(); }

private:
    void runLoop();

    std::atomic<bool> m_running;
    std::atomic<bool> m_paused;
    unsigned int m_interval_us; // microseconds
    unsigned int m_busy_wait_us; // microseconds
    bool m_invoke_main;
    int64_t m_repeatCount; // -1 = infinite

    std::function<void()> m_callback;
    std::thread m_thread;

    // synchronization for pause/resume/stop
    std::mutex m_mutex;
    std::condition_variable m_cv;
};

#endif // TIMERTHREAD_H
