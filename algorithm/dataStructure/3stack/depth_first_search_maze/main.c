#include <stdio.h>
#include "stack_list_c.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXROW 10
#define MAXLINE 10
Point coordinate[MAXROW][MAXLINE];
//typedef struct _Point
//{
//    int _x;
//    int _y;
//}Point;
/*
int maze[MAXROW][MAXLINE] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
    0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
    1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,
    1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,
    1,1,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,
    1,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,0,1,1,
    1,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,
    1,1,1,0,0,0,1,1,0,0,0,0,1,1,1,1,0,1,1,1,
    1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,
    1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,
    1,1,1,0,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1,
    1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,
    1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,0,1,1,1,
    1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,
    1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,
    1,1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};
*/

int maze[MAXROW][MAXLINE]={
    1,1,1,1,1,1,1,1,1,1,
    0,0,0,1,1,1,1,1,1,1,
    1,1,0,1,1,1,1,1,1,1,
    1,1,0,0,0,0,1,1,1,1,
    1,1,0,1,1,0,1,1,1,1,
    1,1,0,1,1,0,1,1,1,1,
    1,1,1,1,1,0,1,1,1,1,
    1,1,1,1,1,0,0,0,1,1,
    1,1,1,1,1,1,1,0,0,0,
    1,1,1,1,1,1,1,1,1,1,
};

void dismaze()
{
    for (int i = 0; i < MAXROW; i++)
    {
        for (int j = 0; j < MAXLINE; j++)
        {
            if (maze[i][j] == 1)
            {
                printf(" *"); //墙
            }
            else if (maze[i][j] == 2)
            {
                printf(" #");
            }
            else
            {
                printf("  ");
            }
        }
        putchar(10);
    }
    printf("=========================\n");
}

void visitpushstack(Stacklist *sl, int x, int y, Point p)
{
    Point t = {x, y};
    push(sl, t);

    coordinate[x][y] = p;
}

void discoordinate()
{
    for (int i = 0; i < MAXROW; i++)
    {
        for (int j = 0; j < MAXLINE; j++)
        {
            printf("(%2d,%2d)", coordinate[i][j]._x, coordinate[i][j]._y);
        }
        putchar(10);
    }
    printf("========================\n");
}

int main()
{
    dismaze();
    Point sp = {1, 0}, ep = {8, 9};
    // Point sp={1, 0}, ep = {0,19};
    Stacklist sl;
    initStacklist(&sl);
    push(&sl, sp);

    memset(coordinate, 0xff, sizeof(coordinate));
//    discoordinate();
#if 1
    int flag = 0;
    Point t = {0, 0};
    while (!isempty(&sl))
    {
        t = pop(&sl);
        maze[t._x][t._y] = 2;

        system("cls");
        dismaze();
        sleep(1);
        //上 下 左 右
        //右
        if (t._y + 1 <= 9 && maze[t._x][t._y + 1] != 1 && maze[t._x][t._y + 1] != 2)
        {
            visitpushstack(&sl, t._x, t._y + 1, t);
        }
        //上
        if (t._x - 1 >= 0 && maze[t._x - 1][t._y] != 1 && maze[t._x - 1][t._y] != 2)
        {
            visitpushstack(&sl, t._x - 1, t._y, t);
        }
        //下
        if (t._x + 1 <= 9 && maze[t._x + 1][t._y] != 1 && maze[t._x + 1][t._y] != 2)
        {
            visitpushstack(&sl, t._x + 1, t._y, t);
        }
        //左
        if (t._y - 1 >= 0 && maze[t._x][t._y - 1] != 1 && maze[t._x][t._y - 1] != 2)
        {
            visitpushstack(&sl, t._x, t._y - 1, t);
        }
        // //右
        // if (t._y + 1 <= 9 && maze[t._x][t._y + 1] != 1 && maze[t._x][t._y + 1] != 2)
        // {
        //     visitpushstack(&sl, t._x, t._y + 1, t);
        // }

        if (t._x == ep._x && t._y == ep._y)
        {
            flag = 1;
            break;
        }
    }
    
    if (flag == 1)
    {
        printf("find path!\n");
    }
    else
    {
        printf("not find path!\n");
    }

    discoordinate();
    
    Point tmp = ep;
    while (tmp._y != -1)
    {
        printf("(%2d,%2d)", tmp._x, tmp._y);
        tmp = coordinate[tmp._x][tmp._y];
    }
    putchar(10);
#endif

    return 0;
}
