#include <iostream>
#include <stack>
#include <vector>
#include <stdint.h>

using namespace std;

struct EdgeNode
{
    int verNodeIndex;
    EdgeNode *next;
};

struct VertexNode
{
    int data;
    EdgeNode *head;
};

struct Graph
{
    std::vector<VertexNode> g;
    int nodeNum;
};

void createGraph(Graph &graph, vector<vector<int>> &m, int n)
{
    std::vector<VertexNode> &g = graph.g;
    graph.nodeNum = n;
    g.resize(n);

    for (int i = 0; i < n; i++)
    {
        g[i].data = i;
        g[i].head = NULL;

        for (int j = n - 1; j >= 0; j--)
        {
            if (m[i][j] != 0)
            {
                EdgeNode *edgeNode = new EdgeNode;
                edgeNode->verNodeIndex = j;
                edgeNode->next = g[i].head; // 头插法
                g[i].head = edgeNode;
            }
        }
    }
}

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

EdgeNode *findFirstNeighborNode(VertexNode &verNode, int* visited)
{
    EdgeNode *p = verNode.head;
    while (p != NULL) // 4.找到一个和当前结点相邻且未被访问的邻接点。
    {
        if (visited[p->verNodeIndex] == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void visit(Graph &g, int index, int *visited)
{
    printf("%d ", index + 1);
    visited[index] = 1;
}

void DFS(Graph &graph, int start, int *visited)
{
    std::stack<int> s;
    visit(graph, graph.g[start].data, visited); // 1.访问起始节点，并标记为已访问，入栈
    s.push(start);

    while (!s.empty()) // 2.进入while循环，循环条件是栈是否为空
    {
        int x = s.top(); // 3. 出栈
        s.pop();

        EdgeNode *p = findFirstNeighborNode(graph.g[x], visited); // 4.找到一个和当前结点相邻且未被访问的邻接点。
        while (p != NULL)
        {
            visit(graph, p->verNodeIndex, visited); // 5.访问邻接点，并标记为已访问，入栈。
            s.push(p->verNodeIndex);
            p = findFirstNeighborNode(graph.g[p->verNodeIndex], visited);
        }   // 6.如果某个节点的邻接点都访问完了，则跳到最外层的while循环，进行结点回退。
    }
}

void DFS_Traverse(Graph &graph, int start)
{
    int visited[graph.nodeNum] = {0};
    DFS(graph, start, visited);

    for (int i = 0; i < graph.nodeNum; i++) // 处理非连通图的情况。
    {
        if (visited[i] == 0)
        {
            DFS(graph, i, visited);
        }
    }

    cout << endl;
}

void test_DFS()
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
        DFS_Traverse(g, i);
    }

    clearGraph(g);
}

int main()
{
    test_DFS();

    return 0;
}