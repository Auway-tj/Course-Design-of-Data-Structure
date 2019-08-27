#ifndef DICE_H
#define DICE_H

#include <QDialog>
#include <QTime>
#include <QPainter>

#define dice_window_Height      500
#define dice_window_Width       400
#define DICE_PIX    240 //骰子图片为240pix*240pix
#define	DICE_MAX	6   //骰子最大值为6
#define	LOOP_TIME	10  //掷骰子次数
#define PAUSE_MSEC  100 //暂停时间100ms
#define IMG_PATH    "/image/" //存图片的路径

//暂停观看效果函数
void pause(int msec);
void dice_num(int& num);

namespace Ui {
class Dice;
}

class Dice : public QDialog
{
    Q_OBJECT

public:
    explicit Dice(QWidget *parent = nullptr);
    ~Dice();
    int return_random() const;//返回生成的随机数
    void display();//显示一帧

private slots:
    void on_Button_ok_clicked();

private:
    Ui::Dice *ui;
    int random_num;//最终的随机数

    void paintEvent(QPaintEvent *);//绘制事件
};

#endif // DICE_H
