#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //设置启动画面
    QPixmap pixmap(":/images/startup.jpg");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();
    //设置在启动画面的同时可以用鼠标操作
    a.processEvents();
    //保持画面2s
    Sleep(2000);
    //显示主窗口
    MainWindow w;
    w.setWindowTitle("MiniMusicPlatform");
    w.setWindowIcon(QIcon(":/images/MainWindowIcon.jpg"));

    w.show();
    splash->finish(&w);
    return a.exec();

}
