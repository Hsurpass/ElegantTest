#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

typedef pair<int, int> pii;

struct Node {
    int x, y;
    double g, h, f; // g: 实际代价, h: 估计代价, f: 总代价
    Node *parent;

    Node(int, int y, double g, double h, Node *parent)
        : x(x), y(y), g(g), h(h), f(g) {}
};

class BiDirectionalAStar {
    pii start, goal;
    vector<vector<bool>> grid;
    map<pii, Node*> openSet1, openSet2;
    set<pii> closedSet1, closedSet2;

public:
    BiDirectionalAStar(const pii &start, const pii &goal, const vector<vector<bool>> &grid)
        : start(start), goal(goal), grid(grid) {}

    double heuristic(const pii &a, const pii &b) {
        return abs(a.first - b.first) + abs(a.second - b.second);
    }

    vector<pii> reconstructPath(Node *current) {
        vector<> path;
        while (current != nullptr) {
            path.emplace_back(current->x, current->y);
            current = current->parent;
        }
        reverse(path.begin(), path.end());
        return path;
    }

    vector<pii> findPath() {
        openSet1[start] = new Node(start.first, start.second, 0, heuristic(start, goal), nullptr);
        openSet2[goal] = new Node(goal.first, goal.second, 0, heuristic(goal, start), nullptr);

        while (!openSet1.empty() && !openSet2.empty()) {
            Node *current1 = getLowestFNode(openSet1);
            if (closedSet2.find(make_pair(current1->x, current1->y)) != closedSet2.end()) {
                return reconstructPath(current1);
            }

            expandNode(current1, openSet1, closedSet1, openSet2);

            Node *current =Node);
            if (closedSet1.find(make_pair(current2->x, current2->y)) != closedSet1.end()) {
                return reconstructPath(current2);
            }

            expandNode(current2, openSet2, closedSet2, openSet1);
        }

        return {}; // Path not found
    }

private:
    Node* getLowestFNode(map<pii,*> &openSet) {
        Node *lowestFNode = nullptr;
        for (const auto &entry : openSet) {
            if (lowestFNode == nullptr || entry.second->f < lowestFNode->f) {
                lowestFNode = entry.second;
            }
        }
        return lowestFNode;
    }

    void expandNode(Node *current, map<, Node*> &openSet, set<> &closedSet, map<pii, Node*> &otherOpenSet) {
        pii currentPos(current->x, current->y);
        openSet.erase(currentPos);
        closedSet.insert(currentPos);

        const int dx[] = {-1, 0, 1, 0};
        const int dy[] = {0, 1, 0, -1};

        for (int i = 0;            int nx = current->x + dx[i], ny = current->y + dy[i];
            if (nx <0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size()) continue;
            if (grid[nx][ny]) continue; // Skip if the cell is blocked

            double g = current->g + 1;
            double h = heuristic({nx, ny}, otherOpenSet.begin()->second->parent->parent == nullptr
                                            ? start
                                            : make_pair(otherOpenSet.begin()->second->parent->x, otherOpenSet.begin()->second->parent->y));
            double f = g + h;

            pii newPos(nx, ny);
            if (closedSet.find(newPos) != closedSet.end() && f >= current->f) continue;

            if (openSet.find(newPos) == openSet.end() || f <Pos]->f) {
                openSet[newPos] = new Node(nx, ny, g, h, current);
            }
        }
    }
};

int main() {
    pii start(0, 0);
    pii goal(4, 4);
    vector<vector<bool>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    }; // 0 represents unblocked cells and 1 represents blocked cells

    BiDirectionalAStar bidirectionalAStar(start, goal, grid);
    vector<pii> path = bidirectionalAStar.findPath();

    cout << "Path from start to goal: " <<;
    for (auto p : path) {
        cout << <<.first << " << p.second << ")" <<;
    }

    return 0;
}

