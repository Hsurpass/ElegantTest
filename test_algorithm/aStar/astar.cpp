#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

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

    void reset() { f = g = h = -1; parent = NULL; }
    bool operator<(const Node& other) const { return this->f < other.f; }
    bool operator>(const Node& other) const { return this->f > other.f; }
    // bool operator==(const Node& other) const { return this->p.x == other.p.x && this->p.y == other.p.y; }

};

class Astar
{
public:
    ~Astar();
    void initMap();
    bool findPath(Point start, Point end);
    void getOneNeighborNode(int x, int y, int g, Node* curr, Node* end);
    void printPath();

    vector<vector<Node *>> aStarMap;
    std::priority_queue<Node, vector<Node>, std::greater<Node> > openList;  // 小顶堆
    vector<Node*> path;
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

void Astar::initMap()
{
    aStarMap.resize(10);
    for (int i = 0; i < 10; i++)
    {
        vector<Node*>& map = aStarMap[i];
        for (int j = 0; j < 10; j++)
        {
            Node *node = new Node();
            node->p.x = i;
            node->p.y = j;
            node->type = NodeType_none;

            map.push_back(node);
        }
    }

    Node*& node = aStarMap[2][3];
    node->type = NodeType_wall;
    aStarMap[2][3]->type = NodeType_wall;
    aStarMap[3][3]->type = NodeType_wall;
    aStarMap[4][3]->type = NodeType_wall; 
    aStarMap[5][3]->type = NodeType_wall;
    aStarMap[5][4]->type = NodeType_wall;
    aStarMap[2][5]->type = NodeType_wall;
    aStarMap[3][5]->type = NodeType_wall;
    aStarMap[4][5]->type = NodeType_wall; 
    aStarMap[5][5]->type = NodeType_wall;

    aStarMap[2][4]->type = NodeType_wall;

}

void Astar::getOneNeighborNode(int x, int y, int g, Node* curr, Node* end)
{
    if ((x < 0 || x >= 10) || (y < 0 || y >= 10) )
        return ;

    Node* neighborNode = aStarMap[x][y];
    if (neighborNode == NULL || neighborNode->type == NodeType_wall || neighborNode->type == NodeType_close || neighborNode->type == NodeType_open)
    {
        return ;
    }
    
    neighborNode->h = abs(end->p.x - x) + abs(end->p.y - y);
    neighborNode->g = curr->g + g;
    neighborNode->f = neighborNode->g + neighborNode->h;
    neighborNode->type = NodeType_open;
    neighborNode->parent = curr;

    openList.push(*neighborNode);    
}

bool Astar::findPath(Point start, Point end)
{
    if(start.x < 0 || start.y < 0 || end.x < 0 || end.y < 0)
    {
        cout << "start or end fail!!!" << endl;
        return false;
    }

    Node* startNode = aStarMap[start.x][start.y];
    startNode->g = 0;
    Node* endNode = aStarMap[end.x][end.y];
    if(startNode->type == NodeType_wall || endNode->type == NodeType_wall)
    {
        cout << "not arrive" << endl;
        return false;
    }

    openList.push(*startNode);

    while (!openList.empty())
    {
        Node currNode = openList.top();
        openList.pop();
        Node* realNode = aStarMap[currNode.p.x][currNode.p.y];
        realNode->type = NodeType_close;

        if (currNode.p.x == end.x && currNode.p.y == end.y) // 找到终点了
        {
            Node* endNode = aStarMap[end.x][end.y];
            while (endNode)
            {
                path.push_back(endNode);
                endNode = endNode->parent;
            }
            std::reverse(path.begin(), path.end());

            cout << "find Path" << endl;
            return true;
        }

        // 上 x-1, y
        getOneNeighborNode(currNode.p.x - 1, currNode.p.y, 10, realNode, endNode);        
        
        // 下 x+1, y
        getOneNeighborNode(currNode.p.x + 1, currNode.p.y, 10, realNode, endNode);

        // 左 x, y-1
        getOneNeighborNode(currNode.p.x, currNode.p.y - 1, 10, realNode, endNode);

        // 右 x, y+1
        getOneNeighborNode(currNode.p.x, currNode.p.y + 1, 10, realNode, endNode);

        // 左上
        getOneNeighborNode(currNode.p.x - 1, currNode.p.y - 1, 14, realNode, endNode);

        // 右上
        getOneNeighborNode(currNode.p.x - 1, currNode.p.y + 1, 14, realNode, endNode);

        // 左下
        getOneNeighborNode(currNode.p.x + 1, currNode.p.y - 1, 14, realNode, endNode);

        // 右下
        getOneNeighborNode(currNode.p.x + 1, currNode.p.y + 1, 14, realNode, endNode);
        
    }
    
    cout << "not find path" << endl;

    return false;
}

void Astar::printPath()
{
    for (int i = 0; i < path.size(); i++)
    {
        cout << "(" << path[i]->p.x << ", " << path[i]->p.y << ")";
    }
    cout << endl;
}

int main()
{
    Astar astar;
    astar.initMap();
    Point start{3, 1};
    // Point end{3, 6};
    // Point end{3, 4};
    Point end{9, 9};


    astar.findPath(start, end);
    astar.printPath();

    return 0;
}