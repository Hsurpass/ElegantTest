#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define COSTMAX INT8_MAX
#define N 6

void dijkstra(int matrix[][N], int v, int *path)
{
    // 1.根据邻接矩阵初始化起点v到其他顶点的距离值, 并标记为已访问
    int dis[N] = {COSTMAX};
    int visited[N] = {0};
    for (int i = 0; i < N; i++)
    {
        dis[i] = matrix[v][i];
        visited[i] = 0;
        path[i] = v;
    }
    visited[v] = 1; // 标记起点为已访问
    path[v] = -1;   // 记录起点的父节点

    int nodeCount = N;
    while (--nodeCount > 0) // 遍历N-1次
    {
        // 2.从距离表中选择较小值的结点并标记为已访问。
        int minDis = COSTMAX;
        int w = v;
        for (int j = 0; j < N; j++) // 使用遍历的方式找到最小值
        {
            if (!visited[j] && dis[j] < minDis)
            {
                minDis = dis[j];
                w = j;
            }
        }
        visited[w] = 1;

        // 处理非连通图的情况
        if (minDis == COSTMAX)
        {
            return;
        }

        // 3.如果当前结点w的值 + 从当前结点w到其他未被访问过的结点的距离 小于 距离表中的值，则更新距离表同时记录下父节点。
        for (int j = 0; j < N; j++)
        {
            if (!visited[j] && (dis[w] + matrix[w][j]) < dis[j])
            {
                dis[j] = dis[w] + matrix[w][j];
                path[j] = w;
            }
        }

    } // 4. 重复步骤2、3直至图中的所有结点都被访问。
}

void printPath(int* path, int v, int end)
{
    if(v < 0 || end >= N) { cout << "start and end is invalid value!" << endl; return; }

    vector<char> route;
    route.push_back(end +'A');

    int parent = path[end];
    while (parent != v)
    {
        route.push_back(parent +'A');
        parent = path[parent];
    }
    route.push_back(v +'A');
    std::reverse(route.begin(), route.end());
    for(auto &x:route)
    {
        printf("%c->", x);
    }
    printf("null\n");
}

/*
    1->2: 1
    1->3: 12
    2->3: 9
    2->4: 3
    3->5: 5
    4->3: 4
    4->5: 13
    4->6: 15
    5->6: 4
           A  B  C  D  E  F
           0  1  2  3  4  5
    A   0  0  1  12 &  &  &
    B   1  &  0  9  3  &  &
    C   2  &  &  0  &  5  &
    D   3  &  &  4  0  13 15
    E   4  &  &  &  &  &  4
    F   5  &  &  &  &  &  0
*/
void test_dijkstra()
{
    int matrix[N][N] = {
        {0, 1, 12, COSTMAX, COSTMAX, COSTMAX},
        {COSTMAX, 0, 9, 3, COSTMAX, COSTMAX},
        {COSTMAX, COSTMAX, 0, COSTMAX, 5, COSTMAX},
        {COSTMAX, COSTMAX, 4, 0, 13, 15},
        {COSTMAX, COSTMAX, COSTMAX, COSTMAX, COSTMAX, 4},
        {COSTMAX, COSTMAX, COSTMAX, COSTMAX, COSTMAX, 0}};

    int path[N] = { -2 };
    dijkstra(matrix, 0, path);

    // printPath(path, 0, 5);
    for (int i = 0; i < N-1; i++)
    {
        printPath(path, i, 5);
    }
    
}

int main()
{
    test_dijkstra();

    return 0;
}