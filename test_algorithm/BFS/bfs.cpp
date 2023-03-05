#include <iostream>
#include <queue>
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

void BFS(Graph* g, int start, int *visited)
{
    visit(g, start, visited);
    std::queue<int> q;
    q.push(start);

    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        for (int i = 0; i < N; i++)
        {
            if(g->matrix[x][i] == 1 && visited[i] == 0)
            {
                visit(g, i, visited);
                q.push(i);
            }
        }
        
    }
    
}

void BFS_Traversal(int start)
{
    Graph g;
    int m[5][5] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}};
    int visited[N] = {0};
    initGraph(&g, m);

    BFS(&g, start, visited);

    // 处理非连通图的情况
    for (int i = 0; i < N; i++)
    {
        if (visited[i] == 0)
        {
            BFS(&g, i, visited);
        }
    }
    printf("\n");
}

void test_bfs()
{
    for (int i = 0; i < N; i++)
    {
        BFS_Traversal(i);    
    }
}


int main()
{
    test_bfs();

    return 0;
}