#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QIntValidator* IntValidator = new QIntValidator;
    IntValidator->setRange(MIN_n, MAX_n);
    ui->lineEdit_n->setValidator(IntValidator);//限定n的输入为整数以及整数的范围
    ui->lineEdit_n->setPlaceholderText(QString::fromLocal8Bit("输入范围：1~20"));
    ui->lineEdit_s->setValidator(IntValidator);//限定s的输入为整数以及整数的范围（s定小于n）
    ui->lineEdit_s->setPlaceholderText(QString::fromLocal8Bit("输入范围：1~n"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Button_exit_clicked()//“退出程序”按钮
{
    close();//关闭程序
}

void MainWindow::on_Button_start_clicked()//“开始游戏”按钮
{
    int n, s;//人数，开始人编号
    QString num_str = ui->lineEdit_n->text();//取第一个框中的数据
    //qDebug() << "num_str1:" << num_str << endl;
    if (num_str.isEmpty()){
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请输入游戏人数"));//弹出提示
        return;
    }
    n = num_str.toInt();//转成整数
    if (n == 0){//若n为0
        QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("游戏人数不能为0"));//弹出提示
        return;
    }

    num_str = ui->lineEdit_s->text();//取第二个框的数据
    //qDebug() << "num_str2:" << num_str << endl;
    if (num_str.isEmpty()){
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请输入开始人编号"));//弹出提示
        return;
    }
    s = num_str.toInt();//转成整数
    if (s == 0){//若s为0
        QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("开始人编号不能为0"));//弹出提示
        return;
    }
    else if (s > n){//若s大于n，则报错退出
        QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("注意：s不能大于n！"));//弹出提示
        return;
    }

    //弹出游戏窗口
    Game G;//构造游戏窗口
    G.Init(n, s);//初始化SqList
    G.setFixedSize(game_window_Width, game_window_Height);//固定窗口大小
    G.show();//演示游戏界面
    G.exec();//维持执行状态
}
