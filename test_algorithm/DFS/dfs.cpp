#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#define N 5
typedef struct Node
{
    Node(int i) : index(i) {}
    int index;
} Node;

struct Graph
{
    int matrix[N][N];
    // Node node[N];
};

void initGraph(Graph *g, int (*m)[N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            g->matrix[i][j] = m[i][j];
        }
    }
}

void visit(Graph *g, int index, int *visited)
{
    printf("%d ", index + 1);
    visited[index] = 1;
}

void DFS_recursive(Graph *g, int start, int *visited)
{
    visit(g, start, visited);   // 1.访问当前结点，并标记当前结点为已访问
    for (int i = 0; i < N; i++) // 2.找到一个与当前结点相邻且未被访问的结点
    {
        if (g->matrix[start][i] == 1 && visited[i] == 0)
        {
            DFS_recursive(g, i, visited); // 把邻接点作为当前结点并进行递归操作。
        }
    }
}

// 在push的时候访问结点，结点只被push一次
void DFS_iterative(Graph *g, int index, int *visited)
{
    std::stack<int> s;

    visit(g, index, visited); // 1.访问起始节点
    s.push(index);            // 2.入栈

    while (!s.empty())
    {
        int x = s.top();
        s.pop(); // 3.出栈

        bool haveNeighborNode = true;
        while (haveNeighborNode) //
        {
            for (int i = 0; i < N; i++) // 4.找到当前结点的第一个邻接点
            {
                if (g->matrix[x][i] == 1 && visited[i] == 0)
                {
                    visit(g, i, visited);
                    s.push(i);
                    x = i; // 5.邻接点i作为当前结点，重复步骤4。
                    haveNeighborNode = true;
                    break;
                }
                haveNeighborNode = false; // 6.如果没找到则回退到步骤3出栈，直到栈为空。
            }
        }
    }
}

int getFirstNeighborNode(Graph *g, int findIdx, int *vistied)
{
    if (findIdx < 0 || findIdx >= N)
        return -1;

    for (int i = 0; i < N; i++)
    {
        if (g->matrix[findIdx][i] == 1 && vistied[i] == 0)
        {
            return i;
        }
    }
    return -1;
}

// 在push的时候访问结点，结点只被push一次
void DFS_iterative_push(Graph *g, int index, int *visited)
{
    std::stack<int> s;

    visit(g, index, visited); // 1.访问起始节点
    s.push(index);            // 2.入栈

    while (!s.empty())
    {
        int x = s.top();
        s.pop(); // 3.出栈

        x = getFirstNeighborNode(g, x, visited);    // 4.找到当前结点的第一个邻接点
        while (x >= 0) 
        {
            visit(g, x, visited);
            s.push(x);
            x = getFirstNeighborNode(g, x, visited); // 5.邻接点i作为当前结点，重复步骤4。

        }// 6.如果没找到则回退到步骤3出栈，直到栈为空。
    }
}

// 在pop的时候访问结点，
void DFS_iterative_pop(Graph *g, int index, int *visited)
{
    std::stack<int> s;
    visited[index] = 1; // 标记当前结点已入栈
    s.push(index);      // 入栈

    while (!s.empty())
    {
        int x = s.top();
        printf("%d ", x); // 访问当前结点
        s.pop();          // 出栈

        int i;
        while ((i = getFirstNeighborNode(g, x, visited)) >= 0) // 找到当前结点的第一个邻接点
        {
            visited[i] = 1; // 标记邻接点已入栈
            s.push(i);      // 入栈
            x = i;          // 把邻接点设置为当前结点，继续查找邻接点
        }
    }
}

void DFS_Traverse(int version, int start)
{
    // for (int i = 0;i < N; i++)
    // {
    //     Node n = Node(i);
    // }
    Graph g;
    int m[5][5] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}};
    int visited[N] = {0};
    initGraph(&g, m);
    if (version == 1)
    {
        DFS_recursive(&g, start, visited);
    }
    else if (version == 2)
    {
        DFS_iterative(&g, start, visited);
    }
    else if (version == 3)
    {
        DFS_iterative_push(&g, start, visited);
    }
    else if (version == 4)
    {
        DFS_iterative_pop(&g, start, visited);
    }
    
    // 处理非连通图的情况
    for (int i = 0; i < N; i++)
    {
        if (visited[i] == 0)
        {
            if (version == 1)
            {
                DFS_recursive(&g, i, visited);
            }
            else if (version == 2)
            {
                DFS_iterative(&g, i, visited);
            }
            else if (version == 3)
            {
                DFS_iterative_push(&g, i, visited);
            }
            else if (version == 4)
            {
                DFS_iterative_pop(&g, start, visited);
            }
        }
    }
    printf("\n");
}

void test_dfs()
{
    for (int i = 0; i < N; i++)
    {
        DFS_Traverse(1, i);
        DFS_Traverse(2, i);
        DFS_Traverse(3, i);
        DFS_Traverse(4, i);
        printf("-------------------------------\n");
    }
}

int main()
{
    test_dfs();

    return 0;
}