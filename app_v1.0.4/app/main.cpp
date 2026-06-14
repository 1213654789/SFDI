#include "mainwindow.h"
#include "open_window.h"
#include <QApplication>
#include <QObject>
#include "qdebug.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/photo.ico"));   // 统一设置图标（需将 app.ico 加入资源文件）
    //    MainWindow w;
    open_window w;
    w.show();




    return a.exec();
}
