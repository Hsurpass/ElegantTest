#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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
    NodeType_close,
    NodeType_open,
    NodeType_wall
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
    vector<vector<Node *>> aStarMap;
    std::priority_queue<Node, vector<Node>, std::greater<Node>> openList; // 小顶堆
    vector<Node *> path;
};

Astar::~Astar()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            delete aStarMap[i][j];
        }
    }

    aStarMap.clear();
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
    aStarMap.resize(ROW);
    for (int i = 0; i < ROW; i++)
    {
        vector<Node *> &map = aStarMap[i];
        map.reserve(COL);
        for (int j = 0; j < COL; j++)
        {
            Node *node = new Node();
            node->p.x = i;
            node->p.y = j;

            switch (matrix[i][j])
            {
            case 3:
                node->type = NodeType_wall;
                break;
            default:
                node->type = NodeType_none;
                break;
            }

            map.push_back(node);
        }
    }

    // Node *&node = aStarMap[2][3];
    // node->type = NodeType_wall;
    // aStarMap[2][3]->type = NodeType_wall;
    // aStarMap[3][3]->type = NodeType_wall;
    // aStarMap[4][3]->type = NodeType_wall;
    // aStarMap[5][3]->type = NodeType_wall;
    // aStarMap[5][4]->type = NodeType_wall;
    // aStarMap[2][5]->type = NodeType_wall;
    // aStarMap[3][5]->type = NodeType_wall;
    // aStarMap[4][5]->type = NodeType_wall;
    // aStarMap[5][5]->type = NodeType_wall;

    // aStarMap[2][4]->type = NodeType_wall;
}

void Astar::getOneNeighborNode(int x, int y, int g, Node *curr, Node *end)
{
    if ((x < 0 || x >= ROW) || (y < 0 || y >= COL))
        return;

    Node *neighborNode = aStarMap[x][y];
    if (neighborNode == NULL || neighborNode->type == NodeType_wall || neighborNode->type == NodeType_close)
    {
        return;
    }

    if (neighborNode->type == NodeType_open)
    {
        // 如果经过经过当前节点到达邻接点的G值 比 现在的G值小，则更新F和G值，并重新设置父节点 
        if((curr->g + g) < neighborNode->g)
        {
            neighborNode->g = curr->g + g;
            neighborNode->f = neighborNode->g + neighborNode->h;
            neighborNode->parent = curr;
        }   
    }
    else
    {
        neighborNode->h = abs(end->p.x - x) + abs(end->p.y - y);
        neighborNode->g = curr->g + g;
        neighborNode->f = neighborNode->g + neighborNode->h;
        neighborNode->type = NodeType_open;
        neighborNode->parent = curr;

        openList.push(*neighborNode);
    }
}

bool Astar::findPath()
{
    Node *startNode = aStarMap[m_start.x][m_start.y];
    startNode->g = 0;
    startNode->h = abs(m_end.x - m_start.x) + abs(m_end.y - m_start.y);
    startNode->f = startNode->g + startNode->h;
    Node *endNode = aStarMap[m_end.x][m_end.y];
    if (startNode->type == NodeType_wall || endNode->type == NodeType_wall)
    {
        cout << "not arrive" << endl;
        return false;
    }

    // 1.把起点放到优先队列中
    openList.push(*startNode);

    while (!openList.empty()) // openlist 为空说明没找到路径，跳出循环
    {
        // 2.从openlist中选择F值最小的节点，设置为当前节点，并把它放到closelist中
        const Node &tmpNode = openList.top();
        Node *currNode = aStarMap[tmpNode.p.x][tmpNode.p.y];
        currNode->type = NodeType_close;
        openList.pop();

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

        // 重新调整堆
        // std::priority_queue<Node, vector<Node>, std::greater<Node>> tmpList; // 小顶堆
        // openList.swap()
    }

    cout << "not find path" << endl;

    return false;
}

void Astar::printPath()
{
    Node *endNode = aStarMap[m_end.x][m_end.y];
    while (endNode)
    {
        path.push_back(endNode);
        endNode = endNode->parent;
    }
    std::reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++)
    {
        cout << "(" << path[i]->p.x << ", " << path[i]->p.y << ")";
    }
    cout << endl;
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
        /*6*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*7*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*8*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*9*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    Astar astar;
    astar.initMap(matrix);
    astar.setStart({3, 1});
    astar.setEnd({3, 6});
    // Point start{3, 1};
    // Point end{3, 6};
    // Point end{3, 4};
    // Point end{9, 9};

    astar.findPath();
    astar.printPath();

    return 0;
}