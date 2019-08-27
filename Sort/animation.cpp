#include "animation.h"
#include "ui_animation.h"
#include <QVector>
#include <QDebug>
//绘图
#include <QPainter>
#include <QTime>
//end

//暂停观看效果函数
void pause(int msec){
    QTime ReachTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < ReachTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
/***************************************************
 *
 * 排序类定义
 *
***************************************************/
/*比较函数*/
//相等函数
bool EQ(const KeyType &a, const KeyType &b) {
    return (a == b);
}
//小于函数
bool LT(const KeyType &a, const KeyType &b) {
    return (a < b);
}
//小于等于函数
bool LQ(const KeyType &a, const KeyType &b) {
    return (a <= b);
}
//交换函数（效率高）
void exchange(KeyType &a, KeyType &b) {
    //此时只需交换关键字
    a = a^b;
    b = a^b;
    a = a^b;
}
/******类的相关函数的实现******/
//取得表长
subscript SqList::ListLength() const {
    return subscript (elem.size());
}
//输入表中元素
void SqList::InputList(KTvector in) {
    elem = in;
    return;
}
//打印所有表中元素
void SqList::OutputList() const{
    for (KTvector::const_iterator i = elem.begin(); i < elem.end(); i++)
        qDebug() << *i << ' ';
    qDebug() << endl;
    return;
}
//返回元素中的最大值
void SqList::return_max_min(KeyType& max_n, KeyType& min_n) const{
    subscript len = ListLength();
    for (subscript i = 0; i < len; i++){
        if (0 == i){//首个元素
            max_n = elem.at(i);//赋初值
            min_n = elem.at(i);//赋初值
        }
        else{//非首个元素
            if (elem.at(i) > max_n)//遇到更大的
                max_n = elem.at(i);//记录下来
            if (elem.at(i) < min_n)//遇到更小的
                min_n = elem.at(i);//记录下来
        }
    }
    return;
}
//模拟[]运算符功能
KeyType SqList::at(subscript i) const{
    return elem.at(i);
}
/************插入排序类**********/
//1.1.直接插入排序
void SqList::InsertSort(Animation& A) {
    KeyType temp;//用作哨兵
    subscript i, j;
    for (i = 1; i < ListLength(); i++) {
        if (LT(elem[i], elem[i - 1])) {//小于
            temp = elem[i];//复制哨兵
            elem[i] = elem[i - 1];
            A.display(i-1,i);
            for (j = i - 2; j >= 0 && LT(temp, elem[j]); j--){//与哨兵比较
                elem[j + 1] = elem[j];//将记录后移，腾出位置
                A.display(j + 1, j);
            }
            elem[j + 1] = temp;//将哨兵位置插入
            A.display(j + 1, i);
        }
    }

    A.display(ILLEGAL, ILLEGAL);
    return;
}
//1.2.折半插入排序
void SqList::BiInsertSort(Animation& A) {
    KeyType temp;//用作哨兵
    subscript i, j;
    subscript low, high, mid;//低位与高位与中间位置
    for (i = 1; i < ListLength(); i++) {
        temp = elem[i];//复制哨兵
        low = 0;//设置低位
        high = i - 1;//设置高位
        while (low <= high) {
            mid = (low + high) / 2;//折半二分
            if (LT(temp, elem[mid]))
                high = mid - 1;
            else
                low = mid + 1;
        }
        for (j = i - 1; j >= high + 1; j--){
            elem[j + 1] = elem[j];//将记录后移，腾出位置
            A.display(j + 1, j);
        }
        elem[high + 1] = temp;//将哨兵位置插入
        A.display(high + 1, i);
    }

    A.display(ILLEGAL, ILLEGAL);
    return;
}
//1.3.希尔排序
void SqList::ShellSort(Animation& A) {
    subscript dl = ListLength() / 2;//调用排序次数
    //本算法在此摒弃增量数组，直接利用函数获得增量(增量缩小)
    for (; dl != 1; dl /= 2)//dlta[k] = leng/2^(k)
        ShellInsert(dl, A);//一趟增量的函数，int_pow为整数求幂函数
    ShellInsert(dl, A);//此时dl为1，仍需执行

    A.display(ILLEGAL, ILLEGAL);
    return;
}
//希尔插入函数
void SqList::ShellInsert(const subscript& dk, Animation& A) {
    KeyType temp;//用作哨兵
    subscript i, j;//dk为间隔
    for (i = dk; i < ListLength(); i++) {//i = dk + 1
        if (LT(elem[i], elem[i - dk])) {
            temp = elem[i];//暂存
            for (j = i - dk; j >= 0 && LT(temp, elem[j]); j -= dk){//与哨兵比较
                elem[j + dk] = elem[j];//将记录后移，腾出位置
                A.display(j + dk, j);
            }
            elem[j + dk] = temp;//将哨兵位置插入
            A.display(j + dk, i);
        }
    }
}
/************交换排序类**********/
//2.1.冒泡排序
void SqList::BubbleSort(Animation& A) {
    bool f_change = true;//交换标志
    for (subscript i = ListLength() - 1; i > 0 && f_change; i--) {
        f_change = false;
        for (subscript j = 0; j < i; ++j)
            if (LT(elem[j + 1], elem[j])) {
                exchange(elem[j], elem[j + 1]);
                A.display(j, j + 1);
                f_change = true;
            }
    }

    A.display(ILLEGAL, ILLEGAL);
    return;
}
//2.2.快速排序
void SqList::QuickSort(Animation& A) {
    QSort(0, elem.size() - 1, A);//初始，从头到尾做快排

    A.display(ILLEGAL, ILLEGAL);
    return;
}
//快排递归函数
void SqList::QSort(const subscript& low, const subscript& high, Animation& A) {
    if (low < high) {//对区间[low, high]做快排
        subscript pivotloc = Partition(low, high, A);//得到枢纽位置
        QSort(low, pivotloc - 1, A);//枢纽前作快排
        QSort(pivotloc + 1, high, A);//枢纽后作快排
    }
}
//快排确定枢纽函数
subscript SqList::Partition(subscript low, subscript high, Animation& A) {
    KeyType pivotkey = elem[low];//记录枢纽关键字
    KeyType temp = elem[low];//记录枢纽
    while (low < high) {//自两端向中间扫描
        while (low < high && elem[high] >= pivotkey)
            high--;
        elem[low] = elem[high];//比枢纽小的移动到低端
        A.display(low, high);
        while (low < high && elem[low] <= pivotkey)
            low++;
        elem[high] = elem[low];//比枢纽大的移动到高端
        A.display(low, high);
    }
    elem[low] = temp;//赋枢纽的值
    A.display(low, low);
    return low;//返回枢纽位置
}
/************选择排序类**********/
//3.1.选择排序
void SqList::SelectSort(Animation& A) {
    subscript i, min;
    for (i = 0; i < ListLength() - 1; i++) {//选择i小的记录，并交换
        min = SelectMinKey(i);
        if (i != min){
            exchange(elem[i], elem[min]);
            A.display(i, min);
        }
    }

    A.display(ILLEGAL, ILLEGAL);
    return;
}
//选排范围中，选择关键字最小的位置函数
subscript SqList::SelectMinKey(const subscript& i) {
    subscript j, min = i;
    for (j = i + 1; j < ListLength(); ++j)
        if (!LQ(elem[min], elem[j]))//a>b
            min = j;
    return min;
}

/***************************************************
 *
 * 显示窗体类定义
 *
***************************************************/
Animation::Animation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Animation)
{
    ui->setupUi(this);

    this->resize(sort_window_Width, sort_window_Height);//设置窗体大小
    move_1 = ILLEGAL;
    move_2 = ILLEGAL;
}

Animation::~Animation()
{
    delete ui;
}

void Animation::init(KTvector data_array, int choose_sort)
{
    SL.InputList(data_array);//初始化复制
    sorting_algorithm = choose_sort;//复制
}


void Animation::on_Button_close_clicked()//关闭窗口
{
    close();//关闭窗口
}

void Animation::on_Button_play_clicked()//开始绘制
{
    switch (sorting_algorithm){
    case button_DIRECT_INSERT://直接插入排序
        SL.InsertSort(*this);
        break;
    case button_BINARY_INSERT://折半插入排序
        SL.BiInsertSort(*this);
        break;
    case button_SHELL://希尔排序
        SL.ShellSort(*this);
        break;
    case button_BUBBLE://冒泡排序
        SL.BubbleSort(*this);
        break;
    case button_QUICK://快速排序
        SL.QuickSort(*this);
        break;
    case button_SIMPLE_SELECT://简单选择排序
        SL.SelectSort(*this);
        break;
    default:
        break;
    }
}

//绘图函数1
void Animation::paintEvent(QPaintEvent *)//QPaintEvent *e
{
    int list_len = SL.ListLength();//表长度
    if(!list_len)//m_numList.isEmpty()
        return;

    QPainter painter(this);//绘图类
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::black);//黑色笔

    //绘制底座
    int baseWidth = sort_window_Base_Width;//底座的宽度
    int baseHeight = sort_window_Base_Height;//底座以上上高度，即柱子最大高度
    int baseX = this->width()/2 - baseWidth/2;//底座左起点的横坐标，这使得图标显示居中
    int baseY = baseHeight + sort_window_head_offset;//底座左起点的纵坐标
    painter.drawLine(baseX, baseY, baseX + baseWidth, baseY);//绘制底座(X1, Y1) -> (X2, Y2)

    int gap = sort_window_gap_len;//柱子间的间隙
    int valWidth = baseWidth/list_len - gap;//柱子宽度

    //获取选项中值最大的那个，以这个为基准高度，来计算其他值的高度
    int maxValValue, minValValue;//最大的柱子真值，以此为100%；最小的柱子真值，以此为0%
    SL.return_max_min(maxValValue, minValValue);//取得对应的最大值与最小值
    double unitHeight = double(baseHeight)/double(maxValValue - minValValue);//柱子中KeyType单位高度，浮点数保持精度

    QFont ft;//设置字体
    ft.setPixelSize(sort_window_font_size);
    //********逐条打印********
    for(int i = 0; i < list_len; ++i)//m_answerStrList.count()
    {
        //QString answerStr = m_answerStrList.at(i);
        int selectNum = SL.at(i);//当前数字   m_numList.at(i)
        QString selectNumStr = QString::number(selectNum);//数字转换成字符串类型
        int valX = baseX + i*(valWidth + gap);//柱子的左上角横坐标

        //绘制柱子
        int valHight = int((selectNum - minValValue) * unitHeight) + sort_window_Base_Val;//柱子高度（以最小元素为基准线）
        QRect r = QRect(valX, baseY - valHight, valWidth, valHight);//柱子矩形其区域
        QPainterPath path;
        path.addRect(r);//绘制矩形路径
        if (move_1 == i || move_2 == i)//是移动的两个量
            painter.fillPath(path, Qt::red);//绘制填充柱子矩形区域，红色标注
        else
            painter.fillPath(path, Qt::gray);//绘制填充柱子矩形区域，灰色

        //在柱子下绘制每个选项对应的值
        QFontMetrics metrics(ft);//
        int charWitdh = metrics.width(selectNumStr);//计算字体宽度answerStr
        QRect percentRect;//矩形answerRect
        //对比文字长度和柱子的宽度，比柱状图宽的以文字的长度为基准会画，反之以柱子的宽度来画，保证显示全并居中
        if(charWitdh < valWidth)
            percentRect = QRect(valX, baseY, valWidth, 30);
        else
            percentRect = QRect(valX - (charWitdh - valWidth)/2, baseY, charWitdh, 30);
        painter.drawText(percentRect, Qt::AlignCenter, selectNumStr);//绘制对应值
    }
}
//end


//确定移动的两个量
void Animation::get_move(subscript m1, subscript m2){
    move_1 = m1;
    move_2 = m2;
}
//演示函数
void Animation::display(subscript m1, subscript m2){
    get_move(m1, m2);//取得当前有变动的元素下标
    repaint();//激活绘制事件，更新绘制图像
    pause(sort_window_pause_msec);//暂停100ms，显示效果
}
