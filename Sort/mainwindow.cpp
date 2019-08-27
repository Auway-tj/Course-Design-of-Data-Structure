#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <fstream>
using namespace std;

//主窗口构造函数
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置单选按钮的ID
    BG_input = new QButtonGroup(this);
    BG_input->addButton(ui->Button_input_keyboard, button_INPUT_KEYBOARD);
    BG_input->addButton(ui->Button_input_file, button_INPUT_FILE);

    //设置排序算法单选按钮的ID
    BG_sort = new QButtonGroup(this);
    BG_sort->addButton(ui->Button_direct_insert, button_DIRECT_INSERT);
    BG_sort->addButton(ui->Button_binary_insert, button_BINARY_INSERT);
    BG_sort->addButton(ui->Button_shell, button_SHELL);
    BG_sort->addButton(ui->Button_bubble, button_BUBBLE);
    BG_sort->addButton(ui->Button_quick, button_QUICK);
    BG_sort->addButton(ui->Button_simple_select, button_SIMPLE_SELECT);

}

//主窗口析构函数
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Button_openfile_clicked()//打开文件按钮
{
    QString file_name;//存文件路径名
    file_name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择文件"), "", QString::fromLocal8Bit("文本文档(*.txt)"));//弹出选择文件窗口，最后file_name得到文件路径名

    if (!file_name.isNull()){//选择到文件时
        QApplication::setOverrideCursor(Qt::WaitCursor);//变更鼠标指针textBrowser_filename lineEdit_filename
        ui->lineEdit_filename->setText(file_name);//在单行文本框读出
        QApplication::restoreOverrideCursor();//恢复鼠标指针
    }
    else
        qDebug() << "do not choose the file";
    return;
}

void MainWindow::on_Button_exit_clicked()//退出按钮
{
    close();//直接关闭程序
}

void MainWindow::on_Button_start_clicked()//开始排序按钮
{
    int flag_input = BG_input->checkedId();//取得输入方式按钮ID
    int flag_sort = BG_sort->checkedId();//取得排序方式按钮ID

    qDebug() << "flag_input: " << flag_input;//显示读取回的输入方式与排序算法
    qDebug() << "flag_sort: " << flag_sort;

    /*排序数据来源*/
    if (button_INPUT_KEYBOARD == flag_input){//键盘输入
        QString input_content = ui->plainTextEdit_source_data->toPlainText();//从纯文本框取得数据
        input_content = input_content.simplified();//清除字符串首尾的空格，且字符串中间的空格都转换为一个空格
        input_content = input_content.remove('\n');//清除回车
        if (input_content.isEmpty()){//若文本框内无数据
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请输入需要排序的数据"));//弹出提示
            return;
        }

        QStringList num_list =input_content.split(' ');//分割成多个数

        elem_array.clear();//清空数组，为后续准备
        for (int i=0; i<num_list.count(); i++){
            elem_array.push_back(num_list.at(i).toInt());//逐个读入数组里
            qDebug() << num_list.at(i).toInt() << ' ';
        }
    }
    else if (button_INPUT_FILE == flag_input){//文件输入
        ifstream infile;//打开文件流
        KeyType in_temp;//输入的临时变量
        QString file_name = ui->lineEdit_filename->text();//存文件路径名

        infile.open(file_name.toLatin1().data());//打开文件
        if (!infile.is_open()){//若打开文件失败
            QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("文件打开失败，请检查文件"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);//弹出打开错误的提示
            return;//退出返回
        }

        elem_array.clear();//清空数组，为后续准备
        while (infile >> in_temp){
            elem_array.push_back(in_temp);//逐个读入数组里
            qDebug() << in_temp << ' ';
        }
        infile.close();//关闭文件

        if (elem_array.isEmpty()){//若文件内无数据
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请在文件输入好数据"));//弹出提示
            return;
        }
    }
    else {//未选择输入方式
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请选择“排序数据来源”"));//弹出提示
        return;//退出返回
    }

    /*//未选择排序算法*/
    if (-1 == flag_sort){
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请选择“排序算法”"));//弹出提示
        return;
    }

    /*弹出显示排序动画窗口*/
    Animation A;//构造窗体  = new Animation()
    A.init(elem_array, flag_sort); //动画演示窗体的初始化工作
    A.show();//演示排序动画
    A.exec();//维持执行状态

    return;
}
