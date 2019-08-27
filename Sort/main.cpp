#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(main_window_Width, main_window_Height);//固定窗口大小
    w.show();

    return a.exec();
}
