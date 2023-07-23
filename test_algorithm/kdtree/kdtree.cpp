/*
kd-tree是一种用于数据检索的树形数据结构，用于kd-tree的数据可以是k维数据。
kd-tree为二叉树结构，其每个节点都是k维数据点的超矩形区域。
kd-tree一般用于多维空间关键数据的搜索和最近邻的查询。
其原理是将k维数据按照各维度排序，建立一棵二叉树。
具体地，每次选择一个坐标轴进行划分，并按照此轴上各点的中位数将当前的超矩形划分为两个子区域，左子区域包含所有低于中位数的数据点，右子区域包含所有高于中位数的数据点。
这个过程将递归地一直运行下去，直到区域中只有一个数据点时终止递归。
这样建立的kd-tree具有以下性质：
    对任意结点，其左子树中所有节点的坐标值小于该节点的坐标值，其右子树中所有节点的坐标值大于该节点的坐标值。
    每个结点的分裂轴选择按深度的奇偶性不断循环选择，在数据落入平衡二叉树的情况下，进行最坏查询的时间复杂度为O(n^(1-1/k))，其中k为维数，n为节点数。
基于以上性质，我们可以使用kd-tree进行数据检索和最近邻的查询。
例如，在进行查找时，我们可以通过比较查找点与分割平面的距离来确定从哪个子树开始搜索、可能更接近最近点的子树，从而达到快速查找的目的。

以下是kd-tree的C++实现示例代码：
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

#define INT_MAX std::numeric_limits<int>::max()
const int k = 1; // K-dimensional
// const int k = 2; // K-dimensional
// const int k = 3; // K-dimensional

// 定义数据结构Point，即二维坐标点
struct Point
{
    int x[k];
};

// 定义数据结构Node，即kd-tree的节点
struct Node
{
    Point p;
    Node *left, *right;
};

// 分割平面的对应维度
int depth;

// 以x轴为基准对点进行排序
bool cmpX(const Point& a, const Point& b)
{
    return a.x[0] < b.x[0];
}

// 以y轴为基准对点进行排序
bool cmpY(const Point& a, const Point& b)
{
    return a.x[1] < b.x[1];
}

// 以z轴为基准对点进行排序
bool cmpZ(const Point& a, const Point& b)
{
    return a.x[2] < b.x[2];
}

// 创建节点
Node* newNode(Point pt)
{
    Node* node = new Node;
    node->p = pt;
    node->left = node->right = nullptr;
    return node;
}

// 构建kd-tree
Node* buildKdTree(vector<Point>& points, int start, int end)
{
    if (start >= end)
        return nullptr;

    // 找到中间点
    int mid = (start + end) / 2;

    // 对当前维度排列
    switch (depth) {
    // case 0: sort(points.begin() + start, points.begin() + end, cmpX); break;
    // case 1: sort(points.begin() + start, points.begin() + end, cmpY); break;
    // case 2: sort(points.begin() + start, points.begin() + end, cmpZ); break;

    case 0:
        std::nth_element(points.begin() + start, points.begin() + mid, points.begin() + end, cmpX);
        break;
    case 1:
        std::nth_element(points.begin() + start, points.begin() + mid, points.begin() + end, cmpY);
        break;
    case 2:
        std::nth_element(points.begin() + start, points.begin() + mid, points.begin() + end, cmpZ);
        break;
    }

    // 创建新节点
    Node* node = newNode(points[mid]);

    // 递归处理左右子树
    depth = (depth + 1) % k; // 循环切换维度
    node->left = buildKdTree(points, start, mid);
    node->right = buildKdTree(points, mid + 1, end);

    return node;
}

// 计算两点距离的平方
int distSquare(Point p1, Point p2)
{
    int d = 0;
    for (int i = 0; i < k; i++) {
        int diff = p1.x[i] - p2.x[i];
        d += diff * diff;
    }
    return d;
}

// 搜索kd-tree的nearest neighbor
// pt: 查询点，root: kd-tree根节点，best: 当前最近点，d: 当前最近距离的平方
void nearestNeighborSearch(Node* root, Point pt, Point& best, int& d)
{
    if (root == nullptr)
        return;

    // 计算当前节点到查询点的距离
    int ds = distSquare(root->p, pt);

    // 如果当前节点更近，更新最近点和距离
    if (ds < d) {
        d = ds;
        best = root->p;
    }

    // 计算当前节点分割平面与查询点的距离
    int dl = INT_MAX, dr = INT_MAX;
    switch (depth) {
    case 0:
        dl = (root->left != nullptr) ? (root->left->p.x[0] - pt.x[0]) : INT_MAX;
        dr = (root->right != nullptr) ? (root->right->p.x[0] - pt.x[0]) : INT_MAX;
        break;
    case 1:
        dl = (root->left != nullptr) ? (root->left->p.x[1] - pt.x[1]) : INT_MAX;
        dr = (root->right != nullptr) ? (root->right->p.x[1] - pt.x[1]) : INT_MAX;
        break;
    case 2:
        dl = (root->left != nullptr) ? (root->left->p.x[2] - pt.x[2]) : INT_MAX;
        dr = (root->right != nullptr) ? (root->right->p.x[2] - pt.x[2]) : INT_MAX;
        break;
    }

    // 递归搜索子树
    Node* first = (dl < dr) ? root->left : root->right;
    Node* second = (dl < dr) ? root->right : root->left;
    nearestNeighborSearch(first, pt, best, d);

    // 如果第二个子树可能存在更近的点，再递归搜索它
    if (dl * dl < d) {
        nearestNeighborSearch(second, pt, best, d);
    }
}

void preorder_traversal(Node* root)
{
    if (!root)
        return;

    cout << "(";
    for (int i = 0; i < k; i++) {
        cout << root->p.x[i] << ",";
    }
    cout << ")";
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void inorder_traversal(Node* root)
{
    if (!root)
        return;

    inorder_traversal(root->left);
    cout << "(";
    for (int i = 0; i < k; i++) {
        cout << root->p.x[i] << ",";
    }
    cout << ")";
    inorder_traversal(root->right);
}

/*
    1 2 3 4 5 6 8
                4
            2       6 
          1   3    5  8  
*/
void test_one_dimensional_kd_tree()
{
    // 构建kd-tree
    vector<Point> points = {{1}, {3}, {5}, {2}, {4}, {6}, {8}};
    Node* root = buildKdTree(points, 0, points.size());
    preorder_traversal(root);   // 4 2 1 3 6 5 8
    putchar(10);
    cout << "-----------------------------------" << endl;
    inorder_traversal(root);    // 1 2 3 4 5 6 8
    putchar(10);
}

#if 0
void test_two_dimensional_kd_tree()
{
    // 构建kd-tree
    // vector<Point> points = {{-1, 2}, {1, 1}, {4, 2}, {2, 3}, {3, 5}};
    vector<Point> points = {{2, 3}, {4, 7}, {5, 4}, {7, 2}, {8, 1}, {9, 6}};
    Node* root = buildKdTree(points, 0, points.size());
    inorder_traversal(root);

    // 搜索最近点
    Point query = {2, 2};
    Point nearest = root->p;
    int distance = INT_MAX;
    depth = 0;
    nearestNeighborSearch(root, query, nearest, distance);
    cout << "The nearest neighbor to query point is: (" << nearest.x[0] << "," << nearest.x[1] << ")" << endl;

    // 释放内存
    delete root;
}
#endif

int main()
{
    test_one_dimensional_kd_tree();
    // test_two_dimensional_kd_tree();
    // test_three_dimensional_kd_tree();

    return 0;
}
