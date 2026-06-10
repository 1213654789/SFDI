#include "microtimerworker.h"
#include <QThread>
#include <QDebug>

MicroTimerWorker::MicroTimerWorker(QObject *parent)
    : QObject(parent)
    , m_running(false)
{
}

MicroTimerWorker::~MicroTimerWorker()
{
    stop();
}

void MicroTimerWorker::start()
{
    m_running = true;
    // 直接运行循环（工作线程中调用）
    runLoop();
}

void MicroTimerWorker::stop()
{
    m_running = false;
}

void MicroTimerWorker::runLoop()
{
    while (m_running) {
       auto start = std::chrono::high_resolution_clock::now();
       emit timeout();   // 可能阻塞，但主线程不再被阻塞，所以可以正常处理
       auto end = std::chrono::high_resolution_clock::now();
       auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
       auto sleepTime = std::chrono::microseconds(500) - elapsed;
       if (sleepTime > std::chrono::microseconds(0)) {
           std::this_thread::sleep_for(sleepTime);
       }
   }
   emit finished();
}
