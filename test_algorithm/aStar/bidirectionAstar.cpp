/*
在下面的代码中，我们首先定义了一个Node结构体，用于表示节点:
    Node结构体包含了节点的坐标、从起点到该节点的实际路径长度g、从起点到该节点的估计路径长度h和父节点指针parent。

然后，我们定义了哈希函数和相等函数，用于将Node结构体作为键值存储到哈希表中。
接下来，我们定义了bidirectionalAStar函数，用于实现双向A算法:
    该函数接受一个网格grid、起点start和终点end作为参数，并返回从起点到终点的最短路径。
    在函数中，我们首先定义了起点和终点的搜索队列、哈希表和集合，并将起点和终点分别加入到搜索队列和哈希表中。
    然后，我们开始双向A算法的主循环，从起点和终点分别开始搜索，并在搜索过程中更新搜索队列、哈希表和集合。
    如果从起点和终点分别访问的节点相遇了，说明找到了一条最短路径，我们可以通过回溯来获取该路径。
最后，我们在main函数中定义了一个网格grid、起点start和终点end，并调用bidirectionalAStar函数来查找最短路径。
如果找到了路径，我们将路径输出到控制台上。

*/

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// 定义节点结构体
struct Node
{
    int x, y; // 节点坐标
    int g, h; // 从起点到该节点的实际路径长度g和估计路径长度h
    int f;
    Node *parent; // 父节点指针
    Node(int x, int y, int g, int h, Node *parent) : x(x), y(y), g(g), h(h), f(g + h), parent(parent) {}
};

// 定义哈希函数和相等函数
struct NodeHash
{
    size_t operator()(const Node *node) const
    {
        return hash<int>()(node->x) ^ hash<int>()(node->y);
    }
};
struct NodeEqual
{
    bool operator()(const Node *node1, const Node *node2) const
    {
        return node1->x == node2->x && node1->y == node2->y;
    }
};

int Heuristic(int currX, int currY, Node* end)
{
    int h = abs(currX - end->x) + abs(currY - end->y); // 曼哈顿距离
    return h;
}

void accessNeighborNode(Node *curr, vector<vector<int>> &grid, Node *start, Node *end,
                        priority_queue<Node *, vector<Node *>, function<bool(Node *, Node *)>>& openlist,
                        unordered_set<Node *, NodeHash, NodeEqual> &closelist,
                        unordered_map<Node *, int, NodeHash, NodeEqual> &dist,
                        unordered_map<Node *, Node *, NodeHash, NodeEqual> &parent,
                        bool isForward)
{
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0)
                continue;

            int x = curr->x + dx;
            int y = curr->y + dy;

            if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] == 1) // grid[x][y] == 1 代表障碍物
                continue;

            int g = curr->g + 10;
            // if( (dx == -1 && (dy == -1 || dy == 1)) ||
            //     (dx == 1 && (dy == -1 || dy == 1) )
            // )
            // {
            //     g = curr->g + 14;
            // }
            int h = isForward ? Heuristic(x, y, end) : Heuristic(x, y, start);

            Node *next = new Node(x, y, g, h, curr);
            if (closelist.count(next)) // 如果邻接点已经放入了closelist中，continue
                continue;

            if (!dist.count(next) || g < dist[next]) // 如果临界点没有放入openlist或者已经放入openlist但是有更优的g值
            {
                dist[next] = g;
                parent[next] = curr;
                openlist.push(next);
            }
        }
    }
}

vector<Node *> collectPath(unordered_set<Node *, NodeHash, NodeEqual> &closelist, Node *currNode,
                           unordered_map<Node *, Node *, NodeHash, NodeEqual> &parent1,
                           unordered_map<Node *, Node *, NodeHash, NodeEqual> &parent2)
{
    vector<Node *> path;
    if (closelist.count(currNode)) // 如果另一方向的closelist包含当前点，说明相遇了
    {
        Node *node = currNode;
        while (node)
        {
            path.push_back(node);
            node = parent1[node];
        }
        std::reverse(path.begin(), path.end());

        node = parent2[currNode];
        while (node)
        {
            path.push_back(node);
            node = node->parent;
        }
    }
    return path;
}

// 定义双向A*算法函数
vector<Node *> bidirectionalAStar(vector<vector<int>> &grid, Node *start, Node *end)
{
    // 定义起点和终点的搜索队列
    priority_queue<Node *, vector<Node *>, function<bool(Node *, Node *)>> openlist1([](Node *a, Node *b)
                                                                                     { return a->f > b->f; }); // 从起点开始搜索的队列，按f值（g+h）从小到大排序
    priority_queue<Node *, vector<Node *>, function<bool(Node *, Node *)>> openlist2([](Node *a, Node *b)
                                                                                     { return a->f > b->f; }); // 从终点开始搜索的队列，按f值（g+h）从小到大排序

    // 定义起点和终点的哈希表和集合
    unordered_map<Node *, int, NodeHash, NodeEqual> dist1;      // 从起点到每个节点的实际路径长度
    unordered_map<Node *, int, NodeHash, NodeEqual> dist2;      // 从终点到每个节点的实际路径长度
    unordered_map<Node *, Node *, NodeHash, NodeEqual> parent1; // 从起点到每个节点的父节点指针
    unordered_map<Node *, Node *, NodeHash, NodeEqual> parent2; // 从终点到每个节点的父节点指针
    unordered_set<Node *, NodeHash, NodeEqual> closelist1;      // 从起点已经访问过的节点集合
    unordered_set<Node *, NodeHash, NodeEqual> closelist2;      // 从终点已经访问过的节点集合

    // 将起点和终点分别加入搜索队列和哈希表
    openlist1.push(start);
    openlist2.push(end);
    dist1[start] = 0;
    dist2[end] = 0;

    // 双向A*算法主循环
    while (!openlist1.empty() && !openlist2.empty())
    {
        // 从起点开始搜索
        Node *curr1 = openlist1.top();
        openlist1.pop();
        closelist1.insert(curr1);

        // 如果从起点访问的节点已经被从终点访问过了，说明找到了一条路径
        vector<Node *> path = collectPath(closelist2, curr1, parent1, parent2);
        if (!path.empty())
        {
            return path;
        }

        // 从正向的openlist中取出最优点作为当前点，遍历当前点的临接点。
        accessNeighborNode(curr1, grid, start, end, openlist1, closelist1, dist1, parent1, true);
        /*for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                if (dx == 0 && dy == 0)
                    continue;

                int x = curr1->x + dx;
                int y = curr1->y + dy;

                if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] == 1) // grid[x][y] == 1 代表障碍物
                    continue;

                int g = curr1->g + 1;
                int h = abs(x - end->x) + abs(y - end->y); // 曼哈顿距离

                Node *next = new Node(x, y, g, h, curr1);
                if (closelist1.count(next))
                    continue;

                if (!dist1.count(next) || g < dist1[next])
                {
                    dist1[next] = g;
                    parent1[next] = curr1;
                    openlist1.push(next);
                }
            }
        }*/

        // 从终点开始搜索
        Node *curr2 = openlist2.top();
        openlist2.pop();
        closelist2.insert(curr2);
        // 如果从终点访问的节点已经被从起点访问过了，说明找到了一条路径
        vector<Node *> pathE = collectPath(closelist1, curr2, parent1, parent2);
        if (!pathE.empty())
        {
            return pathE;
        }

        // 从反向的openlist中取出最优点作为当前点，遍历当前点的临接点。
        accessNeighborNode(curr2, grid, start, end, openlist2, closelist2, dist2, parent2, false);
        /*        for (int dx = -1; dx <= 1; dx++)
                {
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        if (dx == 0 && dy == 0)
                            continue;
                        int x = curr2->x + dx;
                        int y = curr2->y + dy;
                        if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] == 1)
                            continue;

                        int g = curr2->g + 1;
                        int h = abs(x - start->x) + abs(y - start->y);
                        Node *next = new Node(x, y, g, h, curr2);
                        if (closelist2.count(next))
                            continue;
                        if (!dist2.count(next) || g < dist2[next])
                        {
                            dist2[next] = g;
                            parent2[next] = curr2;
                            openlist2.push(next);
                        }
                    }
                }*/
    }

    // 如果没有找到路径，返回空
    return vector<Node *>();
}

// 测试代码
int main()
{
    vector<vector<int>> grid = {
        // {0, 0, 0, 0, 0,},
        // {0, 1, 1, 1, 0,},
        // {0, 0, 0, 0, 0,},
        // {0, 1, 1, 1, 0,},
        // {0, 0, 0, 0, 0,}
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0}};
    Node *start = new Node(0, 0, 0, 0, nullptr);
    Node *end = new Node(4, 4, 0, 0, nullptr);
    // Node *end = new Node(3, 5, 0, 0, nullptr);

    vector<Node *> path = bidirectionalAStar(grid, start, end);
    if (path.empty())
    {
        cout << "No path found!" << endl;
    }
    else
    {
        cout << "Path found:" << endl;
        for (int i = 0; i < path.size(); i++)
        {
            cout << "(" << path[i]->x << ", " << path[i]->y << ")";
        }
        cout << endl;
    }

    return 0;
}