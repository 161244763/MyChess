#include "stone.h"

int board[15][15];//全局共用棋盘,默认color为0的row从1-5，color为1的row在6-10
int last_board[15][15];//全局共用历史上一棋盘

Stone::Stone()
{
    id = -1;
    type = KONG;
    side = ZHONG;
    row = -1;
    column = -1;
    is_dead = true;
    over_river = false;
}

//初始化传参行，列，棋子类型，颜色，编号
Stone::Stone(int ID) 
{
    is_dead = false;
    over_river = false;

    struct POSITION
    {
        int row;
        int col;
        TYPE type;
    };

    POSITION position[16] =
    {
        {0,0,JU},
        {0,1,MA},
        {0,2,XIANG},
        {0,3,SHI},
        {0,4,JIANG},
        {0,5,SHI},
        {0,6,XIANG},
        {0,7,MA},
        {0,8,JU},
        {2,1,PAO},
        {2,7,PAO},
        {3,0,BING},
        {3,2,BING},
        {3,4,BING},
        {3,6,BING},
        {3,8,BING}
    };

    id = ID;
    int X = -1;
    int Y = -1;

    if (id < 16)
    {
        side = BLACK;
        X = position[id].row;
        Y = position[id].col;
        row = position[id].row;
        column = position[id].col;
        type = position[id].type;
    }
    else
    {
        side = RED;
        X = 9 - position[id - 16].row;
        Y = position[id - 16].col;
        row = 9 - position[id - 16].row;
        column = position[id - 16].col;
        type = position[id - 16].type;
    }

    board[X][Y] = ID;
}

Stone::~Stone()
{
    
}

//返回棋子类型
Stone::TYPE Stone::getType()
{
    return type;
}

//返回红方或黑方
Stone::SIDE Stone::getSide()
{
    return side;
}

//返回棋子位置
int Stone::getId()
{
    return id;
}

//判断棋子是否死亡
bool Stone::getDead()
{
    return is_dead;
}

//设定判断棋子死亡规则
void Stone::setDead(bool situation)
{
    is_dead = situation;
}

//判断棋子是否过河
bool Stone::getRiver()
{
    return over_river;
}

//设定判断棋子过河规则
void Stone::setRiver(bool situation)
{
    over_river = situation;
}

//返回棋子所在行
int Stone::getRow()
{
    return row;
}

//设置棋子所在行
void Stone::setRow(int X)
{
    row = X;
    if (side == BLACK && row >= 5)
        setRiver(true);
    if (side == RED && row < 5)
        setRiver(true);
}

//返回棋子所在列
int Stone::getColumn()
{
    return column;
}

//设置棋子所在列
void Stone::setColumn(int Y)
{
    column = Y;
}

//移动棋子
void Stone::move_to(int X, int Y)
{

    board[X][Y] = id;   //行棋后位置
    board[row][column] = 0; //行棋前位置
    setRow(X);
    setColumn(Y);
}

//确认棋子位置
bool Stone::check_pos(int X, int Y)
{
    if (X < 0 || X >= 10)
        return false;
    if (Y < 0 || Y >= 9)
        return false;
    return true;
}

//返回棋子移动的位置
int Stone::get_move(int X, int Y)
{
    if (!Stone::check_pos(X, Y))
        return 0;
    return move[X][Y];
}

//设置棋子的移动位置
void Stone::set_move(int X, int Y)
{
    //当前格子没有棋子
    if (!board[X][Y])
        move[X][Y] = 1;
    //当前格子有和行棋方阵营不同的棋子
    else if ((board[X][Y]<16)!=(this->id<16))
        move[X][Y] = 2;
}


//棋子行棋规则
void Stone::build_move()
{
    for (int i = 0;i <= 10;++i)
        for (int j = 0;j <= 9;++j)
            move[i][j] = 0;
    if (is_dead)
    {
        return;
    }
    
    //兵的行棋规则
    if (type == BING)
    {
        //黑方
        if (side == BLACK)
        {
            //过河后可以向前、左、右走
            if(over_river)
            {
                if (Stone::check_pos(row + 1, column)){
                    Stone::set_move(row + 1, column);
                }
                
                if (Stone::check_pos(row, column + 1)){
                    Stone::set_move(row, column + 1);
                }
                
                if (Stone::check_pos(row, column - 1)){
                    Stone::set_move(row, column - 1);
                }
            }
            //过河前只能向前走
            else
            {
                if (Stone::check_pos(row + 1, column)){
                    Stone::set_move(row + 1, column);
                }
            }
        }
        //红方
        else
        {
            if (over_river)
            {
                if (Stone::check_pos(row - 1, column)){
                    Stone::set_move(row - 1, column);
                }
                
                if (Stone::check_pos(row, column + 1)){
                    Stone::set_move(row, column + 1);
                }
                
                if (Stone::check_pos(row, column - 1)){
                    Stone::set_move(row, column - 1);
                }
            }
            else
            {
                if (Stone::check_pos(row -1, column)){
                    Stone::set_move(row -1, column);
                }
            }
        }
    }
    
    //炮的行棋规则
    if (type == PAO)
    {
        for (int i = row + 1;check_pos(i, column);++i)
        {
            //前方没有棋子 炮只能走 不能吃
            if (!board[i][column]){
                set_move(i, column);
            }
            //前方有棋子 炮只能吃 不能走
            else
            {
                for (int j = i + 1;check_pos(j, column);++j)
                {
                    if (board[j][column])
                    {
                        set_move(j, column);
                        break;
                    }
                }
                break;
            }
        }
        
        for (int i = row - 1;check_pos(i, column);--i)
        {
            if (!board[i][column]){
                set_move(i, column);
            }
            else
            {
                for (int j = i - 1;check_pos(j, column);--j)
                {
                    if (board[j][column])
                    {
                        set_move(j, column);
                        break;
                    }
                }
                break;
            }
        }

        for (int i = column + 1;check_pos(row, i);++i)
        {
            if (!board[row][i]){
                set_move(row, i);
            }
            else
            {
                for (int j = i + 1;check_pos(row, j);++j)
                {
                    if (board[row][j])
                    {
                        set_move(row, j);
                        break;
                    }
                }
                break;
            }
        }
        
        for (int i = column - 1;check_pos(row, i);--i)
        {
            if (!board[row][i]){
                set_move(row, i);
            }
            else
            {
                for (int j = i - 1;check_pos(row, j);--j)
                {
                    if (board[row][j])
                    {
                        set_move(row, j);
                        break;
                    }
                }
                break;
            }
        }
    }
    
    //车的行棋规则
    if (type == JU)
    {
        for (int i = row + 1;check_pos(i, column);++i)
        {
            //没有遇到棋子可以直走
            if (!board[i][column]){
                set_move(i, column);
            }
            //遇到棋子 该棋子可以吃 经过该棋子后的各自不能走
            else
            {
                set_move(i, column);
                break;
            }
        }
        
        for (int i = row - 1;check_pos(i, column);--i)
        {
            if (!board[i][column]){
                set_move(i, column);
            }
            else
            {
                set_move(i, column);
                break;
            }
        }

        for (int i = column + 1;check_pos(row, i);++i)
        {
            if (!board[row][i]){
                set_move(row, i);
            }
            else
            {
                set_move(row, i);
                break;
            }
        }
        
        for (int i = column - 1;check_pos(row, i);--i)
        {
            if (!board[row][i]){
                set_move(row, i);
            }
            else
            {
                set_move(row, i);
                break;
            }
        }
    }
    
    //马的行棋规则
    if (type == MA)
    {
        //日字形移动
        if (check_pos(row + 1, column + 2)){
            if (!board[row][column + 1]){
                set_move(row + 1, column + 2);
            }
        }
        
        if (check_pos(row + 1, column - 2)){
            if (!board[row][column - 1]){
                set_move(row + 1, column - 2);
            }
        }

        if (check_pos(row - 1, column + 2)){
            if (!board[row][column + 1]){
                set_move(row - 1, column + 2);
            }
        }
        
        if (check_pos(row - 1, column - 2)){
            if (!board[row][column - 1]){
                set_move(row - 1, column - 2);
            }
        }

        if (check_pos(row + 2, column + 1)){
            if (!board[row + 1][column]){
                set_move(row + 2, column + 1);
            }
        }
        
        if (check_pos(row + 2, column - 1)){
            if (!board[row + 1][column]){
                set_move(row + 2, column - 1);
            }
        }

        if (check_pos(row - 2, column + 1)){
            if (!board[row - 1][column]){
                set_move(row - 2, column + 1);
            }
        }
        
        if (check_pos(row - 2, column - 1)){
            if (!board[row - 1][column]){
                set_move(row - 2, column - 1);
            }
        }
    }
    
    //相的行棋规则
    if (type == XIANG)
    {
        //田字形 且不能过河
        if (side == BLACK)
        {
            if (check_pos(row + 2, column + 2) && row + 2 < 5){
                if (!board[row + 1][column + 1]){
                    set_move(row + 2, column + 2);
                }
            }
            
            if (check_pos(row + 2, column - 2) && row + 2 < 5){
                if (!board[row + 1][column - 1]){
                    set_move(row + 2, column - 2);
                }
            }
            
            if (check_pos(row - 2, column + 2) && row - 2 < 5){
                if (!board[row - 1][column + 1]){
                    set_move(row - 2, column + 2);
                }
            }
            
            if (check_pos(row - 2, column - 2) && row - 2 < 5){
                if (!board[row - 1][column - 1]){
                    set_move(row - 2, column - 2);
                }
            }
        }
        else
        {
            if (check_pos(row + 2, column + 2) && row + 2 >= 5){
                if (!board[row + 1][column + 1]){
                    set_move(row + 2, column + 2);
                }
            }
            
            if (check_pos(row + 2, column - 2) && row + 2 >= 5){
                if (!board[row + 1][column - 1]){
                    set_move(row + 2, column - 2);
                }
            }
            
            if (check_pos(row - 2, column + 2) && row - 2 >= 5){
                if (!board[row - 1][column + 1]){
                    set_move(row - 2, column + 2);
                }
            }
            
            if (check_pos(row - 2, column - 2) && row - 2 >= 5){
                if (!board[row - 1][column - 1]){
                    set_move(row - 2, column - 2);
                }
            }
        }
    }
    
    //士的行棋规则
    if (type == SHI)
    {
        //对角线 不能超出九宫格
        if (side == BLACK)
        {
            if (check_pos(row + 1, column + 1) && row + 1 < 3 && column + 1 < 6){
                set_move(row + 1, column + 1);
            }
            
            if (check_pos(row + 1, column - 1) && row + 1 < 3 && column - 1 >= 3){
                set_move(row + 1, column - 1);
            }
            
            if (check_pos(row - 1, column + 1) && column + 1 < 6){
                set_move(row - 1, column + 1);
            }
            
            if (check_pos(row - 1, column - 1) && column - 1 >= 3){
                set_move(row - 1, column - 1);
            }
        }
        else
        {
            if (check_pos(row + 1, column + 1) && column + 1 < 6){
                set_move(row + 1, column + 1);
            }
            
            if (check_pos(row + 1, column - 1) && column - 1 >= 3){
                set_move(row + 1, column - 1);
            }
            
            if (check_pos(row - 1, column + 1) && row - 1 >= 7 && column + 1 < 6){
                set_move(row - 1, column + 1);
            }
            
            if (check_pos(row - 1, column - 1) && row - 1 >= 7 && column - 1 >= 3){
                set_move(row - 1, column - 1);
            }
        }
    }
    
    //将的行棋规则
    if (type == JIANG)
    {
        //一步一格 不能超出九宫格
        if (side == BLACK)
        {
            if (check_pos(row + 1, column) && row + 1 < 3){
                set_move(row + 1, column);
            }
            
            if (check_pos(row - 1, column) && row - 1 < 3){
                set_move(row - 1, column);
            }
            
            if (check_pos(row, column + 1) && column + 1 < 6){
                set_move(row, column + 1);
            }
            
            if (check_pos(row, column - 1) && column - 1 >= 3){
                set_move(row, column - 1);
            }
        }
        else
        {
            if (check_pos(row + 1, column) && row + 1 >= 7){
                set_move(row + 1, column);
            }
            
            if (check_pos(row - 1, column) && row - 1 >= 7){
                set_move(row - 1, column);
            }
            
            if (check_pos(row, column + 1) && column + 1 < 6){
                set_move(row, column + 1);
            }
            
            if (check_pos(row, column - 1) && column - 1 >= 3){
                set_move(row, column - 1);
            }
        }
    }
}


QString Stone::getFilePath()
{
    switch (this->side)
    {
    case RED:
        switch (this->type)
        {
        case JIANG:
            return ":/img/r_j.png";
        case JU:
            return ":/img/r_c.png";
        case MA:
            return ":/img/r_m.png";
        case XIANG:
            return ":/img/r_x.png";
        case SHI:
            return ":/img/r_s.png";
        case PAO:
            return ":/img/r_p.png";
        case BING:
            return ":/img/r_z.png";
        case KONG:
            return "";
        }
        break;
    case BLACK:
        switch (this->type)
        {
        case JIANG:
            return ":/img/b_j.png";
        case JU:
            return ":/img/b_c.png";
        case MA:
            return ":/img/b_m.png";
        case XIANG:
            return ":/img/b_x.png";
        case SHI:
            return ":/img/b_s.png";
        case PAO:
            return ":/img/b_p.png";
        case BING:
            return ":/img/b_z.png";
        case KONG:
            return "";
        }
        break;
    case ZHONG:
        return "";
    }
}
