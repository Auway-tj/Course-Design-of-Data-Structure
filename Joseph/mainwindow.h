#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QIntValidator>
#include <QMessageBox>

#define main_window_Height      300
#define main_window_Width       500
#define MIN_n                   1//最小人数
#define MAX_n                   20//最大人数

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Button_exit_clicked();

    void on_Button_start_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
