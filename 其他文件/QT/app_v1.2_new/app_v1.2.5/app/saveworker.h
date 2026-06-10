#ifndef SAVEWORKER_H
#define SAVEWORKER_H

#include <QImage>
#include <QDir>
#include <QMutex>
#include <QAtomicInt>
#include <QVector>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <queue>

class SaveWorker
{
public:
    explicit SaveWorker(const QString &savePath = QString(), const QString &format = "bmp");
    ~SaveWorker();

    void setSavePath(const QString &path);
    void setFormat(const QString &fmt);
    // enqueue image from any thread; returns quickly
    void enqueueImage(const QImage &image);
    // request stop and block until internal thread exits
    void stop();

private:
    void ensurePathExists(const QString &p);
    QString makeFileName();

    QMutex m_mutex;
    std::queue<QImage> m_queue;
    std::condition_variable_any m_cv;
    std::thread m_thread;
    QString m_savePath;
    QString m_format; // e.g. "BMP", "PNG", "JPG"
    QAtomicInt m_counter;
    std::atomic<bool> m_running;
};

#endif // SAVEWORKER_H
