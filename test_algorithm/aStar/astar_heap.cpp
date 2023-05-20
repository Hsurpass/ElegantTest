#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

#include "../../test_cpp/2STL/stl_containers/2apapterContainer/my_heap_template.h"
using namespace std;

#define ROW 10
#define COL 10

/*
    0  1  2  3  4  5  6  7  8  9
  0 0  0  0  0  0  0  0  0  0  0
  1 0  0  0  0  0  0  0  0  0  0
  2 0  0  0  1  0  1  0  0  0  0
  3 0  0  0  1  0  1  0  0  0  0
  4 0  0  0  1  0  1  0  0  0  0
  5 0  0  0  1  1  1  0  0  0  0
  6 0  0  0  0  0  0  0  0  0  0
  7 0  0  0  0  0  0  0  0  0  0
  8 0  0  0  0  0  0  0  0  0  0
  9 0  0  0  0  0  0  0  0  0  0
*/

typedef struct Point
{
    int x;
    int y;
} Point;

enum NodeType
{
    NodeType_none,
    NodeType_wall,
    NodeType_open,
    NodeType_close,
    NodeType_path,
};

class Node
{
public:
    Node() { reset(); }
    Point p;
    int f;
    int g;
    int h;
    NodeType type;
    Node *parent;
    int index;

    void reset()
    {
        f = g = h = -1;
        parent = NULL;
    }
    bool operator<(const Node &other) const { return this->f < other.f; }
    bool operator>(const Node &other) const { return other < *this; }
    // bool operator==(const Node& other) const { return this->p.x == other.p.x && this->p.y == other.p.y; }
};

class Astar
{
public:
    ~Astar();
    void initMap(int matrix[ROW][COL]);
    void setStart(Point start);
    void setEnd(Point end);
    bool findPath();
    void getOneNeighborNode(int x, int y, int g, Node *curr, Node *end);
    void printPath();

    Point m_start;
    Point m_end;
    vector<vector<Node *>> m_aStarMap;
    vector<Node> m_openList;
    vector<Node *> m_path;
};

Astar::~Astar()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            delete m_aStarMap[i][j];
        }
    }

    m_aStarMap.clear();
}

void Astar::setStart(Point start)
{
    if (start.x < 0 || start.y < 0 || start.x >= ROW || start.y >= COL)
    {
        cout << "set start point fail" << endl;
        return;
    }
    m_start = start;
}

void Astar::setEnd(Point end)
{
    if (end.x < 0 || end.y < 0 || end.x >= ROW || end.y >= COL)
    {
        cout << "set end point fail" << endl;
        return;
    }
    m_end = end;
}

void Astar::initMap(int matrix[ROW][COL])
{
    m_aStarMap.resize(ROW);
    for (int i = 0; i < ROW; i++)
    {
        vector<Node *> &map = m_aStarMap[i];
        map.reserve(COL);
        for (int j = 0; j < COL; j++)
        {
            Node *node = new Node();
            node->p.x = i;
            node->p.y = j;

            switch (matrix[i][j])
            {
            case 1:
                node->type = NodeType_wall;
                break;
            default:
                node->type = NodeType_none;
                break;
            }
            node->index = i * 10 + j;

            map.push_back(node);
        }
    }

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            printf("%d ", m_aStarMap[i][j]->type);
        }
        cout << endl;
    }

    // Node *&node = m_aStarMap[2][3];
    // node->type = NodeType_wall;
    // m_aStarMap[2][3]->type = NodeType_wall;
    // m_aStarMap[3][3]->type = NodeType_wall;
    // m_aStarMap[4][3]->type = NodeType_wall;
    // m_aStarMap[5][3]->type = NodeType_wall;
    // m_aStarMap[5][4]->type = NodeType_wall;
    // m_aStarMap[2][5]->type = NodeType_wall;
    // m_aStarMap[3][5]->type = NodeType_wall;
    // m_aStarMap[4][5]->type = NodeType_wall;
    // m_aStarMap[5][5]->type = NodeType_wall;

    // m_aStarMap[2][4]->type = NodeType_wall;
}

void Astar::getOneNeighborNode(int x, int y, int g, Node *curr, Node *end)
{
    if ((x < 0 || x >= ROW) || (y < 0 || y >= COL))
        return;

    Node *neighborNode = m_aStarMap[x][y];
    if (neighborNode == NULL || neighborNode->type == NodeType_wall || neighborNode->type == NodeType_close)
    {
        return;
    }

    if (neighborNode->type == NodeType_open)
    {
        // 如果经过经过当前节点到达邻接点的G值 比 现在的G值小，则更新F和G值，并重新设置父节点
        if ((curr->g + g) < neighborNode->g)
        {
            neighborNode->g = curr->g + g;
            neighborNode->f = neighborNode->g + neighborNode->h;
            neighborNode->parent = curr;
        }

        // 调整结点(上浮或下沉)
        int openListCount = m_openList.size();
        for (int i = 0; i < openListCount; ++i)
        {
            if (m_openList[i].p.x == neighborNode->p.x && m_openList[i].p.y == neighborNode->p.y)
            {
                m_openList[i].g = curr->g + g;
                m_openList[i].f = neighborNode->g + neighborNode->h;
                m_openList[i].parent = curr;

                //更改节点value之后，只会发生一种情况，往上调整或者往下调整，即下面两行代码只会有一行有效执行
                upAdjust<Node, true>(&m_openList[0], i);
                downAdjust<Node, true>(&m_openList[0], i, openListCount);
            }
        }
    }
    else
    {
        neighborNode->h = abs(end->p.x - x) + abs(end->p.y - y);
        neighborNode->g = curr->g + g;
        neighborNode->f = neighborNode->g + neighborNode->h;
        neighborNode->type = NodeType_open;
        neighborNode->parent = curr;

        m_openList.emplace_back(*neighborNode);
        pushHeap<Node, true>(&m_openList[0], m_openList.size());
    }
}

bool Astar::findPath()
{
    Node *startNode = m_aStarMap[m_start.x][m_start.y];
    startNode->g = 0;
    startNode->h = abs(m_end.x - m_start.x) + abs(m_end.y - m_start.y);
    startNode->f = startNode->g + startNode->h;
    Node *endNode = m_aStarMap[m_end.x][m_end.y];
    if (startNode->type == NodeType_wall || endNode->type == NodeType_wall)
    {
        cout << "not arrive" << endl;
        return false;
    }

    // 1.把起点放到优先队列中
    m_openList.emplace_back(*startNode);
    pushHeap<Node, true>(&m_openList[0], m_openList.size());

    while (!m_openList.empty()) // openlist 为空说明没找到路径，跳出循环
    {
        // 2.从openlist中选择F值最小的节点，设置为当前节点，并把它放到closelist中
        popHeap<Node, true>(&m_openList[0], m_openList.size());
        const Node &tmpNode = m_openList.back();
        Node *currNode = m_aStarMap[tmpNode.p.x][tmpNode.p.y];
        currNode->type = NodeType_close;
        m_openList.pop_back();

        // 找到终点了，跳出循环
        if (currNode->p.x == m_end.x && currNode->p.y == m_end.y)
        {
            cout << "find Path." << endl;
            return true;
        }

        // 3.处理当前节点的8个邻接点：
        //     如果是墙或者已经在openlist中则不做处理；
        //     如果没在openlist中则放入openlist中，并把当前节点设置为父节点，计算f\g\h；
        //     如果已经在openlist中，则比较经过当前节点到达临邻接点的G值是否比邻接点现在的G值小，如果小则更新G值和F值，并把当前节点设置为父节点。
        // 上 x-1, y
        getOneNeighborNode(currNode->p.x - 1, currNode->p.y, 10, currNode, endNode);

        // 下 x+1, y
        getOneNeighborNode(currNode->p.x + 1, currNode->p.y, 10, currNode, endNode);

        // 左 x, y-1
        getOneNeighborNode(currNode->p.x, currNode->p.y - 1, 10, currNode, endNode);

        // 右 x, y+1
        getOneNeighborNode(currNode->p.x, currNode->p.y + 1, 10, currNode, endNode);

        // 左上
        getOneNeighborNode(currNode->p.x - 1, currNode->p.y - 1, 14, currNode, endNode);

        // 右上
        getOneNeighborNode(currNode->p.x - 1, currNode->p.y + 1, 14, currNode, endNode);

        // 左下
        getOneNeighborNode(currNode->p.x + 1, currNode->p.y - 1, 14, currNode, endNode);

        // 右下
        getOneNeighborNode(currNode->p.x + 1, currNode->p.y + 1, 14, currNode, endNode);
    }

    cout << "not find path" << endl;

    return false;
}

void Astar::printPath()
{
    Node *endNode = m_aStarMap[m_end.x][m_end.y];
    while (endNode)
    {
        m_path.push_back(endNode);
        endNode = endNode->parent;
    }
    std::reverse(m_path.begin(), m_path.end());

    for (int i = 0; i < m_path.size(); i++)
    {
        m_path[i]->type = NodeType_path;
        cout << "(" << m_path[i]->p.x << ", " << m_path[i]->p.y << ")";
    }
    cout << endl;

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            printf("%d ", m_aStarMap[i][j]->type);
        }
        cout << endl;
    }
}

int main()
{
    int matrix[ROW][COL] = {
        /*0  1  2  3  4  5  6  7  8  9*/
        /*0*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*1*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*2*/ {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
        /*3*/ {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
        /*4*/ {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
        /*5*/ {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        /*6*/ {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        /*7*/ {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        /*8*/ {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        /*9*/ {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}};

    Astar astar;
    astar.initMap(matrix);
    // astar.setStart({5, 0});
    // astar.setStart({9, 9});
    astar.setStart({3, 1});
    // astar.setEnd({4, 4});
    astar.setEnd({9, 9});

    astar.findPath();
    astar.printPath();

    return 0;
}