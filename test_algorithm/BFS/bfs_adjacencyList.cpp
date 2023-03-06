#include <iostream>
#include <queue>
#include <vector>
#include <stdint.h>

using namespace std;

struct EdgeNode
{
    int verNodeIndex; // 顶点的索引
    EdgeNode *next;   // 指向下个结点的指针
};

struct VertexNode
{
    int data;       // 顶点的数据
    EdgeNode *head; // 链表的头指针，边表单链表
};

struct Graph // 图的邻接表表示
{
    std::vector<VertexNode> g; // 顶点表
    int nodeNum;
};

// 通过邻接矩阵创建邻接表
void createGraph(Graph &graph, vector<vector<int>> &m, int n)
{
    std::vector<VertexNode> &g = graph.g;
    graph.nodeNum = n;
    g.resize(n);

    for (int i = 0; i < n; i++)
    {
        g[i].data = i;
        g[i].head = NULL;
        // 邻接矩阵的一行代表所有邻接点，也就是边表，由于采用头插法，所以先从最后一个元素开始插入
        for (int j = n - 1; j >= 0; j--)    
        {
            if (m[i][j] != 0)
            {
                EdgeNode *edgeNode = new EdgeNode; // 创建边表的结点。
                edgeNode->verNodeIndex = j;
                edgeNode->next = g[i].head; // 头插法
                g[i].head = edgeNode;
            }
        }
    }
}

// 清空边表的结点
void clearGraph(Graph &graph)
{
    for (int i = 0; i < graph.nodeNum; i++)
    {
        EdgeNode *p = graph.g[i].head;
        while (p != NULL)
        {
            EdgeNode *t = p->next;
            delete p;
            p = t;
        }
    }
}

void visit(Graph &g, int index, int *visited)
{
    printf("%d ", index + 1);
    visited[index] = 1;
}

void BFS(Graph &graph, int start, int *visited)
{
    std::queue<int> q;
    visit(graph, graph.g[start].data, visited);
    q.push(start);

    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        EdgeNode *p = graph.g[x].head;
        while (p != NULL)
        {
            if (visited[p->verNodeIndex] == 0)
            {
                visit(graph, p->verNodeIndex, visited);
                q.push(p->verNodeIndex);
            }
            p = p->next;
        }
    }
}

void BFS_Traverse(Graph &graph, int start)
{
    int visited[graph.nodeNum] = {0};
    BFS(graph, start, visited);

    for (int i = 0; i < graph.nodeNum; i++) // 处理非连通图的情况。
    {
        if (visited[i] == 0)
        {
            BFS(graph, i, visited);
        }
    }

    cout << endl;
}

void test_BFS()
{
    Graph g;
    vector<vector<int>> matrix = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}};

    createGraph(g, matrix, 5);

    for (int i = 0; i < 5; i++)
    {
        BFS_Traverse(g, i);
    }

    clearGraph(g);
}

int main()
{
    test_BFS();

    return 0;
}