#include "mainwindow.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));//取随机数种子
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(main_window_Width, main_window_Height);//固定窗口大小
    w.show();

    return a.exec();
}
