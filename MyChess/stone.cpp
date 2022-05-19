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

    Stone::Stone(int ID) //初始化传参行，列，棋子类型，颜色，编号
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

    Stone::TYPE Stone::getType()
    {
        return type;
    }

    Stone::SIDE Stone::getSide()
    {
        return side;
    }

    int Stone::getId()
    {
        return id;
    }

    bool Stone::getDead()
    {
        return is_dead;
    }

    void Stone::setDead(bool situation)
    {
        is_dead = situation;
    }

    bool Stone::getRiver()
    {
        return over_river;
    }

    void Stone::setRiver(bool situation)
    {
        over_river = situation;
    }

    int Stone::getRow()
    {
        return row;
    }

    void Stone::setRow(int X)
    {
        row = X;
        if (side == BLACK && row >= 5)
            setRiver(true);
        if (side == RED && row < 5)
            setRiver(true);
    }

    int Stone::getColumn()
    {
        return column;
    }

    void Stone::setColumn(int Y)
    {
        column = Y;
    }

    void Stone::move_to(int X, int Y)
    {

        board[X][Y] = id;
        board[row][column] = 0;
        setRow(X);
        setColumn(Y);
    }

    bool Stone::check_pos(int X, int Y)
    {
        if (X < 0 || X >= 10)
            return false;
        if (Y < 0 || Y >= 9)
            return false;
        return true;
    }

    int Stone::get_move(int X, int Y)
    {
        if (!Stone::check_pos(X, Y))
            return 0;
        return move[X][Y];
    }

    void Stone::set_move(int X, int Y)
    {
        if (!board[X][Y])
            move[X][Y] = 1;
        else if ((board[X][Y]<16)!=(this->id<16))
            move[X][Y] = 2;
    }



    void Stone::build_move()
    {

        for (int i = 0;i <= 10;++i)
            for (int j = 0;j <= 9;++j)
                move[i][j] = 0;

        if (is_dead)
        {
            return;
        }
        if (type == BING)
        {
            if (side == BLACK)
            {
                if(over_river)
                {
                    if (Stone::check_pos(row + 1, column))
                        Stone::set_move(row + 1, column);
                    if (Stone::check_pos(row, column + 1))
                                            Stone::set_move(row, column + 1);
                                        if (Stone::check_pos(row, column - 1))
                                            Stone::set_move(row, column - 1);
                                    }
                                    else
                                    {
                                        if (Stone::check_pos(row + 1, column))
                                            Stone::set_move(row + 1, column);
                                    }
                                }
                                else
                                {
                                    if (over_river)
                                    {
                                        if (Stone::check_pos(row - 1, column))
                                            Stone::set_move(row - 1, column);
                                        if (Stone::check_pos(row, column + 1))
                                            Stone::set_move(row, column + 1);
                                        if (Stone::check_pos(row, column - 1))
                                            Stone::set_move(row, column - 1);
                                    }
                                    else
                                    {
                                        if (Stone::check_pos(row -1, column))
                                            Stone::set_move(row -1, column);
                                    }
                                }
                            }
                            if (type == PAO)
                            {
                                for (int i = row + 1;check_pos(i, column);++i)
                                {
                                    if (!board[i][column])
                                        set_move(i, column);
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
                                    if (!board[i][column])
                                        set_move(i, column);
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
                                    if (!board[row][i])
                                        set_move(row, i);
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
                                    if (!board[row][i])
                                        set_move(row, i);
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
                            if (type == JU)
                            {
                                for (int i = row + 1;check_pos(i, column);++i)
                                {
                                    if (!board[i][column])
                                        set_move(i, column);
                                    else
                                    {
                                        set_move(i, column);
                                        break;
                                    }
                                }
                                for (int i = row - 1;check_pos(i, column);--i)
                                {
                                    if (!board[i][column])
                                        set_move(i, column);
                                    else
                                    {
                                        set_move(i, column);
                                        break;
                                    }
                                }

                                for (int i = column + 1;check_pos(row, i);++i)
                                {
                                    if (!board[row][i])
                                        set_move(row, i);
                                    else
                                    {
                                        set_move(row, i);
                                        break;
                                    }
                                }
                                for (int i = column - 1;check_pos(row, i);--i)
                                {
                                    if (!board[row][i])
                                        set_move(row, i);
                                    else
                                    {
                                        set_move(row, i);
                                        break;
                                    }
                                }
                            }
                            if (type == MA)
                            {
                                if (check_pos(row + 1, column + 2))
                                    if (!board[row][column + 1])//
                                        set_move(row + 1, column + 2);
                                if (check_pos(row + 1, column - 2))
                                    if (!board[row][column - 1])
                                        set_move(row + 1, column - 2);

                                if (check_pos(row - 1, column + 2))
                                    if (!board[row][column + 1])
                                        set_move(row - 1, column + 2);
                                if (check_pos(row - 1, column - 2))
                                    if (!board[row][column - 1])
                                        set_move(row - 1, column - 2);

                                if (check_pos(row + 2, column + 1))
                                    if (!board[row + 1][column])
                                        set_move(row + 2, column + 1);
                                if (check_pos(row + 2, column - 1))
                                    if (!board[row + 1][column])
                                        set_move(row + 2, column - 1);

                                if (check_pos(row - 2, column + 1))
                                    if (!board[row - 1][column])
                                        set_move(row - 2, column + 1);
                                if (check_pos(row - 2, column - 1))
                                    if (!board[row - 1][column])
                                        set_move(row - 2, column - 1);
                            }
                            if (type == XIANG)
                            {
                                if (side == BLACK)
                                {
                                    if (check_pos(row + 2, column + 2) && row + 2 < 5)
                                        if (!board[row + 1][column + 1])
                                            set_move(row + 2, column + 2);
                                    if (check_pos(row + 2, column - 2) && row + 2 < 5)
                                        if (!board[row + 1][column - 1])
                                            set_move(row + 2, column - 2);
                                    if (check_pos(row - 2, column + 2) && row - 2 < 5)
                                        if (!board[row - 1][column + 1])
                                            set_move(row - 2, column + 2);
                                    if (check_pos(row - 2, column - 2) && row - 2 < 5)
                                        if (!board[row - 1][column - 1])
                                            set_move(row - 2, column - 2);
                                }
                                else
                                {
                                    if (check_pos(row + 2, column + 2) && row + 2 >= 5)
                                        if (!board[row + 1][column + 1])
                                            set_move(row + 2, column + 2);
                                    if (check_pos(row + 2, column - 2) && row + 2 >= 5)
                                        if (!board[row + 1][column - 1])
                                            set_move(row + 2, column - 2);
                                    if (check_pos(row - 2, column + 2) && row - 2 >= 5)
                                        if (!board[row - 1][column + 1])
                                            set_move(row - 2, column + 2);
                                    if (check_pos(row - 2, column - 2) && row - 2 >= 5)
                                        if (!board[row - 1][column - 1])
                                            set_move(row - 2, column - 2);
                                }
                            }
                            if (type == SHI)
                            {
                                if (side == BLACK)
                                {
                                    if (check_pos(row + 1, column + 1) && row + 1 < 3 && column + 1 < 6)
                                        set_move(row + 1, column + 1);
                                    if (check_pos(row + 1, column - 1) && row + 1 < 3 && column - 1 >= 3)
                                        set_move(row + 1, column - 1);
                                    if (check_pos(row - 1, column + 1) && column + 1 < 6)
                                        set_move(row - 1, column + 1);
                                    if (check_pos(row - 1, column - 1) && column - 1 >= 3)
                                        set_move(row - 1, column - 1);
                                }
                                else
                                {
                                    if (check_pos(row + 1, column + 1) && column + 1 < 6)
                                        set_move(row + 1, column + 1);
                                    if (check_pos(row + 1, column - 1) && column - 1 >= 3)
                                        set_move(row + 1, column - 1);
                                    if (check_pos(row - 1, column + 1) && row - 1 >= 7 && column + 1 < 6)
                                        set_move(row - 1, column + 1);
                                    if (check_pos(row - 1, column - 1) && row - 1 >= 7 && column - 1 >= 3)
                                        set_move(row - 1, column - 1);
                                }
                            }
                            if (type == JIANG)
                            {
                                //滹
                                if (side == BLACK)
                                {
                                    if (check_pos(row + 1, column) && row + 1 < 3)
                                        set_move(row + 1, column);
                                    if (check_pos(row - 1, column) && row - 1 < 3)
                                        set_move(row - 1, column);
                                    if (check_pos(row, column + 1) && column + 1 < 6)
                                        set_move(row, column + 1);
                                    if (check_pos(row, column - 1) && column - 1 >= 3)
                                        set_move(row, column - 1);
                                }
                                else
                                {
                                    if (check_pos(row + 1, column) && row + 1 >= 7)
                                        set_move(row + 1, column);
                                    if (check_pos(row - 1, column) && row - 1 >= 7)
                                        set_move(row - 1, column);
                                    if (check_pos(row, column + 1) && column + 1 < 6)
                                        set_move(row, column + 1);
                                    if (check_pos(row, column - 1) && column - 1 >= 3)
                                        set_move(row, column - 1);
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



