#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QButtonGroup>
#include <QTextCodec>
#include <QTranslator>
#include "animation.h"

namespace Ui {
class MainWindow;
}

#define main_window_Height      600
#define main_window_Width       1000
//定义主窗口类
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void send_array(QVector<KeyType>);//不需要有函数体

private slots://建立打开文件的槽
    void on_Button_openfile_clicked();

    void on_Button_exit_clicked();

    void on_Button_start_clicked();

private:
    Ui::MainWindow *ui;
    QButtonGroup *BG_input;//输入按钮组
    QButtonGroup *BG_sort;//算法按钮组
    KTvector elem_array;//元素数组
};

#endif // MAINWINDOW_H
