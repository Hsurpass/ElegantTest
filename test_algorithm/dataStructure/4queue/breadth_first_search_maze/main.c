#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "queuelist_c.h"

#define MAXROW 10
#define MAXLINE 10
Point coordinate[MAXROW][MAXLINE];

int maze[MAXROW][MAXROW]={
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
    for(int i = 0;i < MAXROW;i++)
    {
        for(int j = 0;j < MAXLINE;j++)
        {
            if(maze[i][j] == 1)
            {
                printf(" *");
            }
            else if(maze[i][j] == 2){
                printf(" #");
            }
            else {
                printf("  ");
            }
        }
        putchar(10);
    }
}
void discoordinate()
{
    for(int i = 0;i < MAXROW;i++)
    {
        for(int j = 0;j < MAXLINE;j++)
        {
            printf("(%2d,%2d)",coordinate[i][j].x,coordinate[i][j].y);
        }
        putchar(10);
    }
}

void visitenqueue(PQueue *pq,int x,int y,Point pre)
{
    Point t = {x,y};
    enqueue(pq,t);
    coordinate[x][y] = pre;
}

int main()
{
    dismaze();
    Point sp={1,0},ep={8,9};
    PQueue pq;
    queueinit(&pq);
    enqueue(&pq,sp);
    int flag = 0;

    memset(coordinate,0xff,sizeof(coordinate));


    while (!isqueueempty(&pq))
    {
        Point t = dequeue(&pq);
        maze[t.x][t.y] = 2;

        system("cls");
        dismaze();
//        sleep(1);
        //上下左右
        //上
        if(t.x-1 >= 0 && maze[t.x-1][t.y] == 0)
        {
            visitenqueue(&pq,t.x-1,t.y,t);
        }
        //下
        if(t.x+1 <= 9 && maze[t.x+1][t.y] == 0)
        {
            visitenqueue(&pq,t.x+1,t.y,t);
        }
        //左
        if(t.y-1 >= 0 && maze[t.x][t.y-1] == 0)
        {
            visitenqueue(&pq,t.x,t.y-1,t);
        }
        if(t.y+1 <= 9 && maze[t.x][t.y+1] == 0)
        {
            visitenqueue(&pq,t.x,t.y+1,t);
        }

        if(t.x == ep.x && t.y == ep.y)
        {
            flag = 1;
            break;
        }
    }

    if(flag == 1)
    {
        printf("find path\n");
    }
    else {
        printf("not find path\n");
    }
    printf("------------------------------\n");
    discoordinate();
    printf("------------------------------\n");
    Point path = ep;
    while (path.y != -1) {
        printf("(%2d,%2d)",path.x,path.y);
        path = coordinate[path.x][path.y];
    }
    return 0;
}
