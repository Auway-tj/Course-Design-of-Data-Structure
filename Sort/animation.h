#ifndef ANIMATION_H
#define ANIMATION_H

#include <QDialog>
#include <QVector>

//绘图
#include <QMap>
#include <QList>
#include <QString>
//end

#define button_INPUT_KEYBOARD   11
#define button_INPUT_FILE       12
#define button_DIRECT_INSERT    21
#define button_BINARY_INSERT    22
#define button_SHELL            23
#define button_BUBBLE           24
#define button_QUICK            25
#define button_SIMPLE_SELECT    26

#define sort_window_Height      800//显示界面窗口高度
#define sort_window_Width       800//显示界面窗口宽度
#define sort_window_Base_Width  500//底座的宽度
#define sort_window_Base_Height 500//底座以上上高度，即柱子最大高度
#define sort_window_Base_Val    20//柱子基本高度
#define sort_window_gap_len     2//柱子间缝隙间隔长度
#define sort_window_head_offset 100//显示图表处与顶边距离
#define sort_window_font_size   8//显示字体大小
#define sort_window_pause_msec  100//暂停毫秒数：100ms
#define ILLEGAL                 -1//非法值，用于显示
typedef int KeyType;//定义基本关键字类型
typedef QVector<KeyType> KTvector;	//定义元素向量类型
typedef int subscript;				//下标，数组长度等有符号整数类型

class Animation;
/********定义顺序表这一类********/
class SqList {
protected://类的元素
    KTvector elem;//存放待排序元素向量线性表
    /*算法辅助函数*/
    void ShellInsert(const subscript& dk, Animation& A);//希尔插入函数
    void QSort(const subscript& low, const subscript& high, Animation& A); //快排递归函数
    subscript Partition(subscript low, subscript high, Animation& A);//快排确定枢纽函数
    subscript SelectMinKey(const subscript& i);//选排范围中，选择关键字最小的位置函数
public://类的相关函数声明
    /*类基本函数*/
    subscript ListLength() const;//取得表长，可以用来判断表是否建立成功
    void InputList(KTvector in);//输入表中元素
    void OutputList() const;//打印所有表中元素
    void return_max_min(KeyType& max_n, KeyType& min_n) const;//返回元素中的最大值
    KeyType at(subscript i) const;//模拟[]运算符功能

    /*排序算法*/
    //1. 插入排序类
    void InsertSort(Animation& A);	//1.1.直接插入排序
    void BiInsertSort(Animation& A);//1.2.折半插入排序
    void ShellSort(Animation& A);	//1.3.希尔排序
    //2. 交换排序类
    void BubbleSort(Animation& A);	//2.1.冒泡排序
    void QuickSort(Animation& A);	//2.2.快速排序
    //3. 选择排序类
    void SelectSort(Animation& A);	//3.1.选择排序
};

namespace Ui {
class Animation;
}

class Animation : public QDialog
{
    Q_OBJECT

public:
    explicit Animation(QWidget *parent = nullptr);
    ~Animation();
    void display(subscript m1, subscript m2);//演示函数

public slots:
    void init(KTvector, int);//初始化 data_array

private slots:
    void on_Button_close_clicked();
    void on_Button_play_clicked();

private:
    Ui::Animation *ui;
    SqList SL;//封装的线性数组
    int sorting_algorithm;
    subscript move_1, move_2;//变更的两个元素

    //绘画
    void paintEvent(QPaintEvent *);//
    void get_move(subscript m1, subscript m2);//

    //end
};

void pause(int msec);

#endif // ANIMATION_H

