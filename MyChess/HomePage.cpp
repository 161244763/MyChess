#include "HomePage.h"
#include <QPainter>
#include <QFile>

//绘制主菜单
HomePage::HomePage(QWidget *parent)
    : QWidget{parent}
{
    // 设置按钮信息
    btStart.setParent(this);      //指定父对象
    btStart.setText("开始游戏");   //给按钮设置内容
    btQuit.setParent(this);       //指定父对象
    btQuit.setText("退出游戏");    //给按钮设置内容

    // 定义信号
    connect(&btStart,&QPushButton::pressed,this,&HomePage::on_ButtonStart_Click);
    connect(&btQuit,&QPushButton::pressed,this,&HomePage::close);
}

HomePage::~HomePage(){}

void HomePage::paintEvent(QPaintEvent *event)
{
    //绘制首页
    QPainter p(this);
    QPixmap  HomePageImg(":/img/Logo.png");

    // 获取窗口和图片的大小
    float pWidth = HomePageImg.width();
    float pHeight = HomePageImg.height();
    float wWidth = this->width();
    float wHeight = this->height();
    float bWidth = btStart.width();
    float bHeight = btStart.height();

    // 图片水平居中，垂直偏上
    float left = (wWidth - pWidth) / 2;
    float top = (wHeight - pHeight) / 5;
    p.drawPixmap(left, top, pWidth, pHeight, HomePageImg);

    // 设置按钮位置
    left = (wWidth - bWidth) / 2;
    top = top + pHeight + 5;
    btStart.move(left, top);
    btQuit.move(left, (top + bHeight + 5));
}

// 自定义槽函数，游戏开始
void HomePage::on_ButtonStart_Click()
{
    // 调用Board绘制棋盘
    board.resize(590,640);
    board.show();

    // 隐藏首页界面
    this->hide();
}

// 自定义槽函数，退出游戏
void HomePage::on_ButtonQuit_Click()
{

}
