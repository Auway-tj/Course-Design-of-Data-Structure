#include "dice.h"
#include "ui_dice.h"
#include <QDebug>

//暂停观看效果函数
void pause(int msec){
    QTime ReachTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < ReachTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

//掷骰子，返回一个数（1-6）
void dice_num(int& num) {
    num = qrand() % DICE_MAX + 1;
}

Dice::Dice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dice)
{
    ui->setupUi(this);
}

Dice::~Dice()
{
    delete ui;
}

//返回生成的随机数
int Dice::return_random() const{
    return random_num;
}
void Dice::paintEvent(QPaintEvent *)//QPaintEvent
{
    QPainter painter(this);
    QPixmap pix;
    QString applicationDirPath = QCoreApplication::applicationDirPath();

    int base_X, base_Y;
    base_X = base_Y = (dice_window_Width - DICE_PIX)/2;

    pix.load(applicationDirPath + IMG_PATH + "dice_" + QString::number(random_num, 10) + ".png");//加载图片像素
    painter.drawPixmap(base_X, base_Y, DICE_PIX, DICE_PIX, pix);//绘图
}

void Dice::on_Button_ok_clicked()//“确定”按钮
{
    close();//直接关闭窗口
}

void Dice::display(){
    for(int i = 0; i < LOOP_TIME; i++){//循环10次掷骰子后退出
        dice_num(random_num);//掷骰子取得随机数
        repaint();//激活绘制事件，更新绘制图像
        pause(PAUSE_MSEC);//暂停100ms，显示效果
    }
}
