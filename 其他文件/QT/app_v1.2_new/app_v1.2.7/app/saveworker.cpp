#include "saveworker.h"
#include <QDateTime>
#include <QFileInfo>
#include <QDebug>

static QString makeFileNameStatic(const QString &path, const QString &fmt, int id)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss.zzz");
    QString fname = QString("%1_%2.%3").arg(timestamp).arg(id, 4, 10, QChar('0')).arg(fmt.toLower());
    return QDir(path).filePath(fname);
}

SaveWorker::SaveWorker(const QString &savePath, const QString &format)
    : m_savePath(savePath),
      m_format(format.toUpper()),
      m_counter(0),
      m_running(false)
{
    if (m_savePath.isEmpty()) {
        m_savePath = QDir::currentPath() + "/myImage/";
    }
    ensurePathExists(m_savePath);

    // start internal thread
    m_running.store(true);
    m_thread = std::thread([this]() {
        while (m_running.load()) {
            QImage img;
            {
                QMutexLocker locker(&m_mutex);
                if (m_queue.empty()) {
                    // wait until new item or stop
                    m_cv.wait(m_mutex);
                }
                if (!m_queue.empty()) {
                    img = m_queue.front();
                    m_queue.pop();
                }
            }
            if (!img.isNull()) {
                int id = m_counter.fetchAndAddRelaxed(1);
                QString fileName = makeFileNameStatic(m_savePath, m_format, id);
                bool ok = img.save(fileName, m_format.toUtf8().constData());
                if (!ok) qDebug() << "SaveWorker: failed to save" << fileName;
            }
        }

        // flush remaining
        while (true) {
            QImage img;
            {
                QMutexLocker locker(&m_mutex);
                if (m_queue.empty()) break;
                img = m_queue.front();
                m_queue.pop();
            }
            if (!img.isNull()) {
                int id = m_counter.fetchAndAddRelaxed(1);
                QString fileName = makeFileNameStatic(m_savePath, m_format, id);
                bool ok = img.save(fileName, m_format.toUtf8().constData());
                if (!ok) qDebug() << "SaveWorker: failed to save" << fileName;
            }
        }
    });
}

SaveWorker::~SaveWorker()
{
    stop();
}

void SaveWorker::setSavePath(const QString &path)
{
    QMutexLocker locker(&m_mutex);
    m_savePath = path;
    ensurePathExists(m_savePath);
}

void SaveWorker::setFormat(const QString &fmt)
{
    QMutexLocker locker(&m_mutex);
    m_format = fmt.toUpper();
}

void SaveWorker::ensurePathExists(const QString &p)
{
    QDir d(p);
    if (!d.exists()) {
        d.mkpath(p);
    }
}

void SaveWorker::enqueueImage(const QImage &image)
{
    if (!m_running.load()) return;
    QMutexLocker locker(&m_mutex);
    m_queue.push(image);
    m_cv.notify_one();
}

void SaveWorker::stop()
{
    bool expected = m_running.load();
    if (!expected) return;
    m_running.store(false);
    m_cv.notify_one();
    if (m_thread.joinable()) m_thread.join();
}
