#ifndef GAME_H
#define GAME_H

#include <QDialog>

#define game_window_Height      900
#define game_window_Width       1200
#define game_window_centerX     400//图形演示界面圆中心X
#define game_window_centerY     400//图形演示界面圆中心Y
#define game_window_radius      300//图形演示界面圆半径
#define PERSON_PIX              75 //人物图片为75pix*75pix
#define STEP_MSEC               500 //暂停时间500ms
#define alive_name              "alive"
#define dead_name               "dead"
#define circle_name             "circle"

#define OK		    1
#define ERROR		-1

typedef bool ElemType;	//可根据需要修改元素的类型。默认为bool
typedef int Status;	//定义函数返回类型

void calcu_point(QPoint& p, double theta, int r, int x0, int y0);

class Game;//预先声明

namespace Ui {
class Game;
}
//单向循环链表类的类定义
class SqList {
protected://类的元素：无
    ElemType* elem;//元素存储空间
    int length;//顺序表大小
    int num_alive;//在场上存活人数量

    //运行时参数
    int cur;//当前指向的人
    int round;//回合
    void go_next(int& cur) const;//往后走一格
public://类的相关函数声明
    SqList();//建立表
    ~SqList();//销毁表
    void Init(int n, int s);//初始化表
    int ListLength() const;//取得表长（友元函数）
    void ListOutput() const;//打印所有表中元素
    int return_cur() const;//返回cur值
    ElemType at(int i) const;//类似[]运算符
    Status Joseph(int m, Game& G, Ui::Game *&ui);//执行每一回合的约瑟夫环
};



class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();
    void Init(int rn, int rs);//初始化
    void display();//显示画面

private slots:
    void on_Button_close_clicked();

    void on_Button_dice_clicked();

private:
    Ui::Game *ui;
    SqList SL;//建立一个顺序表

    void paintEvent(QPaintEvent *);//绘制事件
};



#endif // GAME_H
