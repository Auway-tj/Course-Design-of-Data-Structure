#include "game.h"
#include "ui_game.h"
#include "dice.h"
#include <QDebug>
#include <QtMath>
using namespace std;

void calcu_point(QPoint& p, double theta, int r, int x0, int y0){
    p = QPoint(x0 + int(r*qSin(theta)), y0 - int(r*qCos(theta)));//计算出每个点的直角坐标，再减去偏移量
    //qDebug() << "x`=" << r*qSin(theta) << "y`=" <<r*qCos(theta);
}

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
}

Game::~Game()
{
    delete ui;
}

void Game::Init(int rn, int rs){//取得运行参数
    SL.Init(rn, rs);//初始化
}
void Game::on_Button_close_clicked()//“关闭”按钮
{
    close();//关闭窗口
}

void Game::on_Button_dice_clicked()//“掷骰子”按钮
{
    Dice D;//构造掷骰子窗口
    D.setFixedSize(dice_window_Width, dice_window_Height);//固定窗口大小
    D.show();//演示掷骰子界面
    D.display();
    D.exec();//维持执行状态
    SL.Joseph(D.return_random(), *this, ui);//向SqList返回随机数
}
//显示函数
void Game::display(){
    repaint();//激活绘制事件，更新绘制图像
    pause(STEP_MSEC);//暂停1000ms，显示效果
}
//绘制事件
void Game::paintEvent(QPaintEvent *){
    QPoint center_point = QPoint(game_window_centerX, game_window_centerY);//中心点
    QPoint per_point;//圆周上每个需要绘制的点
    int radius = game_window_radius;//半径
    const int num = SL.ListLength();//取得人数
    const int offset = PERSON_PIX/2;
    QPainter painter(this);//画图类
    QString applicationDirPath = QCoreApplication::applicationDirPath();
    QString person_name;//打开人物图片名

    painter.setPen(Qt::black);
    painter.drawEllipse(center_point, radius, radius);//先画圆

    double per_degree = 2*M_PI/ num;//每个弧度值
    //qDebug() << "per_degree=" << per_degree;

    for (int i = 0; i < num; ++i){//每个点逐个打印
        calcu_point(per_point, per_degree*i, radius, game_window_centerX, game_window_centerY);
        //打印头像
        QPixmap pix_person;
        if (SL.at(i))
            person_name = alive_name;
        else
            person_name = dead_name;
        pix_person.load(applicationDirPath + IMG_PATH + person_name + ".png");//加载图片像素
        painter.drawPixmap(per_point.x() - offset, per_point.y() - offset, PERSON_PIX, PERSON_PIX, pix_person);//绘图

        QRect percentRect;//矩形answerRect
        percentRect = QRect(per_point.x() - offset/2, per_point.y() + offset, offset, 30);
        painter.drawText(percentRect, Qt::AlignCenter, QString::number(i + 1));//绘制每个人对应的编号

        //打印圈圈
        QPixmap pix_loop;
        if (i == SL.return_cur()){
            pix_loop.load(applicationDirPath + IMG_PATH + circle_name + ".png");//加载图片像素
            painter.drawPixmap(per_point.x() - offset, per_point.y() - offset, PERSON_PIX, PERSON_PIX, pix_loop);//绘图
        }
    }
}

/******顺序表类的相关函数的实现******/
//建立表（构造函数）
SqList::SqList() {
    elem = nullptr;//
    num_alive = length = 0;
}
//销毁表（析构函数）
SqList::~SqList() {
    if (elem)
        delete[]elem;//最后释放空间
}
//初始化
void SqList::Init(int n, int s){
    elem = new(nothrow) ElemType[qulonglong(n)];//分配n个元素大小的空间
    num_alive = length = elem ? n : 0;//空间申请成功：表长为n；失败：表长为0
    for (int i = 0; i < length; i++)
        elem[i] = true;//通通置为有效
    cur = s - 1;//初始开始的位置
    round = 1;//设第一回合
}

//往后走一格
void SqList::go_next(int& cur) const{
    cur = (cur + 1) % length;
}
//取得表长
int SqList::ListLength() const {
    return length;
}
//打印所有表中元素
void SqList::ListOutput() const {
    for (int i = 0; i < length; i++)
        qDebug() << elem[i];
    qDebug() << endl;
}
//返回cur值
int SqList::return_cur() const{
    return cur;
}
//类似[]运算符
ElemType SqList::at(int i) const{
    return elem[i];
}
//约瑟夫环
Status SqList::Joseph(int m, Game& G, Ui::Game *&ui) {
    //变量：从第s人开始
    if (num_alive == 0) {//场上无人，直接报错退出
        ui->plainTextEdit->appendPlainText(QString::fromLocal8Bit("游戏结束"));
        //qDebug() << QString::fromLocal8Bit("游戏结束");
        return ERROR;
    }
    else if (num_alive == 1) {//当前场上只有最多一个人，则直接输出该人，退出
        --num_alive;
        ui->plainTextEdit->appendPlainText(QString::fromLocal8Bit("胜出者：1号。\n"));
        ui->plainTextEdit->appendPlainText(QString::fromLocal8Bit("游戏结束\n"));
        //qDebug() << QString::fromLocal8Bit("胜出者：") << 1 << QString::fromLocal8Bit("号。")<< endl;
        //qDebug() << QString::fromLocal8Bit("游戏结束") << endl;
        return OK;
    }
    else {//场上多于一个人
        int step, starter;//cur表示当前指向的人，step表示实际需要走的步数，m表示随机要走的步数cur, , m

        ui->plainTextEdit->appendPlainText(QString::fromLocal8Bit("第") + QString::number(round) + QString::fromLocal8Bit("回合："));
        //qDebug() << QString::fromLocal8Bit("第") << round << QString::fromLocal8Bit("回合：");
        starter = cur + 1;//记住开始报数的人
        //G.display();

        for (step = m; ; go_next(cur)) {//设置实际需要走的步数((m % num_alive == 0) ? num_alive : m % num_alive)
            if (elem[cur] == true){//有实际的人
                step--;//走一步
                G.display();
            }
            if (step <= 0)
                break;
        }//循环结束后，cur指向需要删除的人
        elem[cur] = false;//除去该人
        G.display();

        ui->plainTextEdit->appendPlainText(QString::fromLocal8Bit("开始报数人：") + QString::number(starter) + QString::fromLocal8Bit("号"));
        ui->plainTextEdit->appendPlainText(QString::fromLocal8Bit("掷骰子结果：") + QString::number(m) );
        ui->plainTextEdit->appendPlainText(QString::fromLocal8Bit("出局人：") + QString::number(cur + 1) + QString::fromLocal8Bit("号\n"));
        //qDebug() << QString::fromLocal8Bit("开始报数人：") << starter << QString::fromLocal8Bit("号，") << QString::fromLocal8Bit("掷骰子结果：") << m << QString::fromLocal8Bit(", 出局人：") << cur + 1 << QString::fromLocal8Bit("号。");//编号比下标大1
        //qDebug() <<endl;

        while (true) {
            go_next(cur);//cur指向删除后的下一个人
            if (elem[cur] == true)//有实际的人
                break;//退出
        }
        round++;
        if (--num_alive == 1){//仅剩最后一人，其胜利
            --num_alive;
            ui->plainTextEdit->appendPlainText(QString::fromLocal8Bit("胜出者：") + QString::number(cur + 1) + QString::fromLocal8Bit("号！"));
            ui->plainTextEdit->appendPlainText(QString::fromLocal8Bit("游戏结束"));
            //qDebug() << QString::fromLocal8Bit("胜出者：") << cur + 1 << QString::fromLocal8Bit("号。");
            //qDebug() << QString::fromLocal8Bit("游戏结束");
        }

        return OK;
    }
}
