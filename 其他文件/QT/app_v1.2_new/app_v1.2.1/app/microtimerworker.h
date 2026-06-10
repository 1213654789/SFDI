#ifndef MICROTIMERWORKER_H
#define MICROTIMERWORKER_H

#include <QObject>
#include <QMutex>
#include <atomic>
#include <chrono>
#include <thread>

class MicroTimerWorker : public QObject
{
    Q_OBJECT
public:
    explicit MicroTimerWorker(QObject *parent = nullptr);
    ~MicroTimerWorker();

public slots:
    // 启动循环（在工作线程中调用）
    void start();
    // 停止循环
    void stop();

signals:
    // 触发超时信号（可连接至 UI 线程的槽函数）
    void timeout();
    // 工作完成信号
    void finished();

private:
    void runLoop();                // 实际循环函数
    std::atomic<bool> m_running;   // 线程安全标志
    QMutex m_mutex;
};

#endif // MICROTIMERWORKER_H
