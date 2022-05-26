#include "board.h"
#include <QPainter>
#include <QFile>
#include <QMouseEvent>

Board::Board(QWidget *parent)
    : QWidget{parent}
{
    // 设置棋子
    for(int i = 0;i<32;i++)
    {
        stones[i] = new Stone(i);
    }

    //设置按钮信息
    btRevert.setParent(this);         //指定父对象
    btRevert.setText("悔   棋");      //给按钮设置内容
    btRestart.setParent(this);       //指定父对象
    btRestart.setText("重启游戏");    //给按钮设置内容

    // 定义信号
    connect(&btRevert,&QPushButton::pressed,this,&Board::On_ButtonClick_btRevert);
    connect(&btRestart,&QPushButton::pressed,this,&Board::On_ButtonClick_btRestart);
}

Board::~Board()
{
}

void Board::paintEvent(QPaintEvent *event)
{
    //绘制棋盘
    QPainter p(this);
    QPixmap boardImg(":/img/board.png");
    //按比例计算棋盘大小
    bWidth = boardImg.width();
    bHeight = boardImg.height();
    wWidth = this->width();
    wHeight = this->height();
    //窗口长宽比
    wScale = wHeight / wWidth;
    //棋盘图片长宽比
    bScale = bHeight / bWidth;
    //距左上角距离
    left = 30,top = 20;
    if(wScale>bScale){
        bWidth = wWidth - 60;
        bHeight = bWidth * bScale;
        top = (wHeight - bHeight)/2;
    }else{
        bHeight = wHeight - 60;
        bWidth = bHeight / bScale;
        left = (wWidth - bWidth)/2;
    }
    
    //格子高度
    gHeight = bHeight*72/725;
    //边缘高度
    gbHeight = (bHeight-gHeight*9)/2;
    gbWidth = (bWidth-gHeight*8)/2;
    
    p.drawPixmap(left, top, bWidth, bHeight, boardImg);
    drawStone(p);

    // 设置按钮高度
    btTop = top + bHeight + 5;

    // 设置悔棋按钮位置
    btLeft = left + bWidth/2 - btRevert.width() - 10;
    btRevert.move(btLeft, btTop);

    // 设置重启游戏按钮位置
    btLeft = btLeft + btRevert.width() + 10;
    btRestart.move(btLeft, btTop);
}

void Board::drawStone(QPainter& p)
{
    for(int i=0;i<32;i++)
    {
        //棋子没有死亡时进行绘制
        if(!stones[i]->getDead())
        {
            float sLeft = left + gbHeight  + gHeight * stones[i]->getColumn();
            float sTop =  top + gbWidth + gHeight * stones[i]->getRow();
            //区分选中和未被选中的棋子
            if(i == _selectedID)
            {
                p.drawPixmap(sLeft-30, sTop-30, 70 , 70 , QPixmap(stones[i]->getFilePath()));
            }
            else
            {
                p.drawPixmap(sLeft-30, sTop-30, 60 , 60 , QPixmap(stones[i]->getFilePath()));
            }
        }
        
        //            qDebug()<<sLeft;
        //            qDebug()<<sTop;
    }
}

void Board::set_redTurn()
{
    _redTurn = ! _redTurn;
}

QPoint Board::center(int id)
{
    return center(stones[id]->getRow(),stones[id]->getColumn());
}

QPoint Board::center(int row,int col)
{
    QPoint ret;
    ret.setX( left  + gbHeight +  gHeight * col);
    ret.setY( top + gbWidth + gHeight * row);
    return ret;
}

bool Board::getClickRowCol(QPoint pt, int &row, int &col)
{
    for(row=0; row<=9; ++row)
    {
        for(col=0; col<=8; ++col)
        {
            QPoint distance = center(row, col) - pt;
            if(distance.x() * distance.x() + distance.y() * distance.y() < gHeight*gHeight/4)
                return true;
        }
    }
    return false;
}


void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt =  ev->pos();
    //将pt转化为象棋的行列值
    //判断行列值上有没有子
    int i;
    int row;
    int col;
    bool bRet = getClickRowCol(pt, row, col);
    //qDebug()<<row<<" "<<col;
    if(bRet == false)//棋盘外
    {
        return;
    }
    for(i = 0;i<32;i++)
    {
        //选中某个没被吃掉的棋子 则将其ID设为clickedID
        if(stones[i]->getRow() == row && stones[i]->getColumn() == col && !stones[i]->getDead())
        {
            // 记录棋子移动前的位置
            pre_row = row;
            pre_col = col;

            //qDebug()<<i;
            break;
        }
    }
    // qDebug()<<i;
    {
        if(i < 32)
        {
            _clickedID = i;
        }
        else
        {
            _clickedID = -1;
        }
    }
    //当前没有棋子被选中
    if(_selectedID == -1)
    {
        //选中当前行棋方的某一棋子则重绘
        if((_clickedID != -1) && ((_redTurn&&(_clickedID >= 16))||(!_redTurn&&(_clickedID < 16))))
        {
            _selectedID = _clickedID;
            update();
        }
    }
    //当前已有棋子被选中 则对第二次点击的位置进行分类
    else
    {
        for(int i = 0;i <32 ; i++)
        {
            stones[i]->build_move();
        }
        //已选中的棋子可以移动
        if(stones[_selectedID]->get_move(row,col) == 1)
        {
            stones[_selectedID]->move_to(row,col);
            update();
            last_row = row;
            last_col = col;
            last_selectedID = _selectedID;
            _selectedID = -1;
            set_redTurn();
        }
        //已选中的棋子可以吃该位置的棋子
        else if(stones[_selectedID]->get_move(row,col) == 2)
        {
            //stones[_selectedID]->setRow(row);
            //stones[_selectedID]->setColumn(col);
            stones[_selectedID]->move_to(row,col);
            if(_clickedID != -1)
            {
                stones[_clickedID]->setDead(true);
                last_clickedID = _clickedID;
            }
            update();

            last_row = row;
            last_col = col;
            last_selectedID = _selectedID;
            _selectedID = -1;
            set_redTurn();
        }
        //选中不可移动的位置
        else if(stones[_selectedID]->get_move(row,col) == 0)
        {
            _selectedID = -1;
            _clickedID = -1;
            update();
            return;
        }
    }
}


void Board::saveStep()
{
    //  在没有吃子的情况下悔棋
    if(pre_row != -1)
    {
        stones[last_selectedID]->reset_move();
        stones[last_selectedID]->move_to(pre_row,pre_col);
        if(last_clickedID != -1)
        {
            stones[last_clickedID]->setDead(false);
            last_clickedID = -1;
        }
        set_redTurn();
        last_selectedID = -1;
        pre_col = -1;
        pre_row = -1;
        update();
        return;
    }
    else
    {
        return;
    }

    // 在有吃子的情况下悔棋（待补充）
    // 这个逻辑上稍微有些复杂

}

void Board::resetBoard()
{
    QPainter p(this);

    last_selectedID = -1;
    last_col =-1;
    last_row = -1;

    // 重置棋盘
    stones[0]->reset_board();
    for(int i = 0;i<32;i++)
    {
        stones[i] = new Stone(i);
    }
    update();

    // 重置红方先手（待补充）
    _redTurn = true;

#if 0
    // 下面这种写法违反QT绘图机制，实际运行会出错。
    for(int i=0;i<32;i++)
    {
        //棋子没有死亡时进行绘制
        if(!stones[i]->getDead())
        {
            float sLeft = left + gbHeight  + gHeight * stones[i]->getColumn();
            float sTop =  top + gbWidth + gHeight * stones[i]->getRow();
            //区分选中和未被选中的棋子
            if(i == _selectedID)
            {
                p.drawPixmap(sLeft-30, sTop-30, 70 , 70 , QPixmap(stones[i]->getFilePath()));
            }
            else
            {
                p.drawPixmap(sLeft-30, sTop-30, 60 , 60 , QPixmap(stones[i]->getFilePath()));
            }
        }

        //            qDebug()<<sLeft;
        //            qDebug()<<sTop;
    }
#endif
}

// 悔棋按钮
void Board::On_ButtonClick_btRevert()
{
    saveStep();
}

// 重启游戏按钮
void Board::On_ButtonClick_btRestart()
{
    resetBoard();
}

