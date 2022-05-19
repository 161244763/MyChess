#include "board.h"
#include <QPainter>
#include <QFile>
#include <QMouseEvent>

Board::Board(QWidget *parent)
    : QWidget{parent}
{
    for(int i = 0;i<32;i++){
        stones[i] = new Stone(i);
    }
}

Board::~Board(){}

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
    wScale = wHeight / wWidth;      //窗口长宽比
    bScale = bHeight / bWidth;      //棋盘图片长宽比
    left = 30,top = 30;           //距左上角距离
    if(wScale>bScale){
        bWidth = wWidth - 60;
        bHeight = bWidth * bScale;
        top = (wHeight - bHeight)/2;
    }else{
        bHeight = wHeight - 60;
        bWidth = bHeight / bScale;
        left = (wWidth - bWidth)/2;
    }

    gHeight = bHeight*72/725;      //格子高度
    gbHeight = (bHeight-gHeight*9)/2;    //边缘高度
    gbWidth = (bWidth-gHeight*8)/2;

    p.drawPixmap(left, top, bWidth, bHeight, boardImg);
    drawStone(p);


//    //绘制棋子
//    float sScale = bWidth / boardImg.width();     //棋子缩放比例
//    float space = 57 * sScale;
//    qDebug()<<sScale;
//    qDebug()<<space;
//    for(int i=0;i<32;i++){
//        float sLeft = 40 + 57 * stones[i]->getColumn();
//        float sTop = 40 + 57 * stones[i]->getRow();
//        p.drawPixmap(sLeft, sTop, 60 , 60 , QPixmap(stones[i]->getFilePath()));
//        qDebug()<<sLeft;
//        qDebug()<<sTop;
//    }
}

void Board::drawStone(QPainter& p)
{
    for(int i=0; i<32; i++)
    {
        drawStone(p, i);
    }
}

void Board::drawStone(QPainter& p,int id )
{
        for(int i=0;i<32;i++)
        {
            if(!stones[i]->getDead())
            {
                float sLeft = left + gbHeight  + gHeight * stones[i]->getColumn();
                float sTop =  top + gbWidth + gHeight * stones[i]->getRow();
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
    qDebug()<<row<<" "<<col;
    if(bRet == false)//棋盘外
    {
        return;
    }
    for(i = 0;i<32;i++)
    {
        if(stones[i]->getRow() == row && stones[i]->getColumn() == col && stones[i]->getDead() == false)
        {
            qDebug()<<i;
            break;
        }
    }
    qDebug()<<i;
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
    if(_selectedID == -1)
    {
        if((_clickedID != -1) && ((_redTurn&&(_clickedID >= 16))||(!_redTurn&&(_clickedID < 16))))
        {
            _selectedID = _clickedID;
            update();
        }

    }

    else
    {
        for(int i = 0;i <32 ; i++)
        {
            stones[i]->build_move();
        }
        if(stones[_selectedID]->get_move(row,col) == 1)
        {
            stones[_selectedID]->move_to(row,col);
            update();
            _selectedID = -1;
            set_redTurn();
        }
        else if(stones[_selectedID]->get_move(row,col) == 2)
        {
            //stones[_selectedID]->setRow(row);
            //stones[_selectedID]->setColumn(col);
            stones[_selectedID]->move_to(row,col);
            if(_clickedID != -1)
            {
                stones[_clickedID]->setDead(true);
            }
            update();

            _selectedID = -1;
            set_redTurn();
        }
        else if(stones[_selectedID]->get_move(row,col) == 0)
        {
            _selectedID = -1;
            _clickedID = -1;
            update();
            return;
        }
    }
}


