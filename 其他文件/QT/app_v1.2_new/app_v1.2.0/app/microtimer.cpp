#include "microtimer.h"
#include <thread>
#include <chrono>

MicroTimer::MicroTimer(QObject *parent)
    : QThread(parent), m_running(false), m_interval(100)
{
}

MicroTimer::~MicroTimer()
{
    stop();
    wait(); // 确保线程退出
}

void MicroTimer::setInterval(long microseconds)
{
    m_interval = microseconds;
}

void MicroTimer::stop()
{
    m_running = false;
}

void MicroTimer::run()
{
    m_running = true;
    while (m_running) {
        // 记录开始时间（可选，用于补偿）
        auto start = std::chrono::high_resolution_clock::now();

        // 发射超时信号（槽函数将在主线程执行）
        emit timeout();

        // 计算需要睡眠的时间
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        long sleepTime = m_interval - elapsed;
        if (sleepTime > 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
        } else {
            // 如果执行时间已超过间隔，则立即进入下一次循环（可能需要警告）
            // 可根据需要添加补偿或直接继续
        }
    }
}
