#include "mainwindow.h"
#include "control_window.h"
#include <QApplication>
#include <QObject>
#include "qdebug.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Ensure application icon is set early so OS/taskbar uses it
    QIcon appIcon = QIcon(":/img/photo.ico");
    if (appIcon.isNull()) appIcon = QIcon(":/img/photo.png");
    if (appIcon.isNull()) appIcon = QIcon(":/img/photo.ioc");
    if (!appIcon.isNull()) QApplication::setWindowIcon(appIcon);
    else qDebug() << "main: application icon resource not found (tried .ico .png .ioc)";

    control_window w;
    w.show();




    return a.exec();
}
