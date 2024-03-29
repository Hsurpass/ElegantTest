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
#include <utility>
#include <vector>
#include <map>
#include <unordered_map>
#include <math.h>

using namespace std;

#define INT_MAX std::numeric_limits<int>::max()
#define FLOAT_MAX std::numeric_limits<float>::max()

const int k = 1; // K-dimensional
// const int k = 2; // K-dimensional
// const int k = 3; // K-dimensional

// 定义数据结构Point，即二维坐标点
struct Point
{
    float x[k];
};

// 定义数据结构Node，即kd-tree的节点
struct Node
{
    Point p;
    Node *left, *right;

    Node() : left(nullptr), right(nullptr)
    {}
    Node(Point pt, Node* l = nullptr, Node* r = nullptr) : p(pt), left(l), right(r)
    {}
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
float distSquare(Point p1, Point p2)
{
    float d = 0;
    for (int i = 0; i < k; i++) {
        float diff = p1.x[i] - p2.x[i];
        d += diff * diff;
    }
    return d;
}

// 存储N个最近的点
vector<Point> nearPoints;
// map<float, Point> nearPts;
vector<std::pair<float, Point>> nearPts;

 // 搜索kd-tree的nearest neighbor
// pt: 查询点，root: kd-tree根节点，best: 当前最近点，d: 当前最近距离的平方
void nearestNeighborSearch(Node* root, Point pt, Point& best, float& bestDis)
{
    if (root == nullptr)
        return;

    // 计算当前节点到查询点的距离
    float ds = distSquare(root->p, pt);
    nearPts.emplace_back(ds, root->p);
    // 如果当前节点更近，更新最近点和距离
    if (ds < bestDis) {
        bestDis = ds;
        best = root->p;

        nearPoints.emplace_back(best);
    }

    // 计算当前节点分割平面与查询点的距离
    float dl = FLOAT_MAX, dr = FLOAT_MAX;
    switch (depth) {
    case 0:
        dl = (root->left != nullptr) ? (root->left->p.x[0] - pt.x[0]) : FLOAT_MAX;
        dr = (root->right != nullptr) ? (root->right->p.x[0] - pt.x[0]) : FLOAT_MAX;
        break;
    case 1:
        dl = (root->left != nullptr) ? (root->left->p.x[1] - pt.x[1]) : FLOAT_MAX;
        dr = (root->right != nullptr) ? (root->right->p.x[1] - pt.x[1]) : FLOAT_MAX;
        break;
    case 2:
        dl = (root->left != nullptr) ? (root->left->p.x[2] - pt.x[2]) : FLOAT_MAX;
        dr = (root->right != nullptr) ? (root->right->p.x[2] - pt.x[2]) : FLOAT_MAX;
        break;
    }

    depth = (depth + 1) % k; // 循环切换维度

    dl = fabs(dl);
    dr = fabs(dr);
    // 递归搜索子树
    Node* first = (dl < dr) ? root->left : root->right;
    Node* second = (dl < dr) ? root->right : root->left;
    nearestNeighborSearch(first, pt, best, bestDis);

    // 如果第二个子树可能存在更近的点，再递归搜索它
    float dis = (dl < dr) ? dr : dl;
    if (dis * dis < bestDis) {
        nearestNeighborSearch(second, pt, best, bestDis);
    }
}

Node* insert(Node* root, Point& pt)
{
    if (root == nullptr) {
        Node* node = new Node(pt);
        return node;
    }
    else if (pt.x[depth] < root->p.x[depth]) {
        depth = (depth + 1) % k;
        root->left = insert(root->left, pt);
    }
    else {
        depth = (depth + 1) % k;
        root->right = insert(root->right, pt);
    }

    return root;
}

Node* kdtree_insert(Node* root, Point pt)
{
    if (root == nullptr) {
        root = new Node(pt);
        return root;
    }

    depth = 0;
    insert(root, pt);

    return root;
}

void destroy_kdtree(Node* root)
{
    if (root == nullptr)
        return;

    destroy_kdtree(root->left);
    destroy_kdtree(root->right);

    delete root;
    root = nullptr;
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
#if 0
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

    // 搜索最近点
    // Point query = {7.5};
    // Point query = {6.5};
    Point query = {5.5};
    // Point query = {4.5};

    Point nearest = root->p;
    float distance = std::numeric_limits<float>::max();
    depth = 0;
    nearestNeighborSearch(root, query, nearest, distance);
    cout << "The nearest neighbor to query point is: (" << nearest.x[0] << ")" << endl;
    for (auto& point : nearPoints) {
        for (int i = 0; i < k; i++) {
            cout << "(" << point.x[i] << ",";
        }
        cout << ")";
    }
    cout << endl;

    for (auto& pt : nearPts) {
        cout << "dis:" << pt.first << "; ";
        for (int i = 0; i < k; i++) {
            cout << "(" << pt.second.x[i] << ",";
        }
        cout << ")" << endl;
    }
    cout << endl;

    destroy_kdtree(root);
}
#endif

/*
    1 2 3 4 5 6 8
                4
            2       6 
          1   3    5  8  
*/
void test_one_dimension_insert()
{
    Node* root = nullptr;
    Point pt;
    pt.x[0] = 1;
    root = kdtree_insert(root, pt);
    pt.x[0] = 2;
    root = kdtree_insert(root, pt);
    pt.x[0] = 3;
    root = kdtree_insert(root, pt);
    pt.x[0] = 4;
    root = kdtree_insert(root, pt);
    pt.x[0] = 5;
    root = kdtree_insert(root, pt);
    pt.x[0] = 6;
    root = kdtree_insert(root, pt);
    pt.x[0] = 7;
    root = kdtree_insert(root, pt);
    pt.x[0] = 8;
    root = kdtree_insert(root, pt);

    // cout << root->p.x[0] << endl;

    preorder_traversal(root);   // 1 2 3 4 5 6 8
    putchar(10);
    cout << "-----------------------------------" << endl;
    inorder_traversal(root);    // 1 2 3 4 5 6 8
    putchar(10);

    destroy_kdtree(root);
}

#if 0
void test_two_dimensional_kd_tree()
{
    // 构建kd-tree
    // vector<Point> points = {{-1, 2}, {1, 1}, {4, 2}, {2, 3}, {3, 5}};
    vector<Point> points = {{2, 3}, {4, 7}, {5, 4}, {7, 2}, {8, 1}, {9, 6}};
    Node* root = buildKdTree(points, 0, points.size());
    inorder_traversal(root);    // (2,3), (5,4), (4,7), (7,2), (8,1), (9,6)
    putchar(10);

    // 搜索最近点
    // Point query = {2, 2};
    // Point query = {4.1, 4.1};
    // Point query = {2.1, 3.1};
    Point query = {2, 4.5};

    Point nearest = root->p;
    float distance = FLOAT_MAX;
    depth = 0;
    nearestNeighborSearch(root, query, nearest, distance);
    cout << "The nearest neighbor to query point is: (" << nearest.x[0] << "," << nearest.x[1] << ")" << endl; // (2,3)

    for (auto& pt : nearPts) {
        cout << "dis:" << pt.first << "; (";
        for (int i = 0; i < k; i++) {
            cout << pt.second.x[i] << ",";
        }
        cout << ")" << endl;
    }

    // 释放内存
    destroy_kdtree(root);
}
#endif

int main()
{
    // test_one_dimensional_kd_tree();
    test_one_dimension_insert();

        // test_two_dimensional_kd_tree();

    return 0;
}
