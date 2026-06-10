#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <atomic>
#include <functional>
#include <thread>

// A simple high-resolution timer using std::thread.
// This class does not use Qt signals/slots to avoid requiring moc.
class TimerThread
{
public:
    explicit TimerThread(unsigned int interval_us = 500, std::function<void()> cb = nullptr);
    ~TimerThread();
    void start();
    void stop();
    void setCallback(std::function<void()> cb);

private:
    void runLoop();

    std::atomic<bool> m_running;
    unsigned int m_interval_us; // microseconds
    std::function<void()> m_callback;
    std::thread m_thread;
};

#endif // TIMERTHREAD_H
