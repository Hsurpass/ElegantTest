#include <initializer_list>
#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <numeric>
#include <limits>

using namespace std;

#if 0
class Point : public std::array<float, 2>
{
public:
    Point()
    {}
    Point(std::array<float, 2>& arr)
    {
        swap(arr);
    }
    static const int DIM = 2;
};
#endif

#if 1
class Point : public std::vector<float>
{
public:
    Point()
    {}
    Point(initializer_list<float> pts) : vector(pts)
    {}
    static const int DIM = 2;
    // static const int DIM = 1;
    // int idx;
};
#endif

struct Node
{
    int idx;    // 原始点的索引
    Node* next[2];  //左右节点
    int axis;   // 划分轴
    Node() : idx(-1), axis(-1)
    {
        next[0] = next[1] = nullptr;
    }
};

template<typename PointType>
class KDTree
{
public:
    Node* root_;
    std::vector<PointType> points_;

    void ClearRecursive(Node* root)
    {
        if (root == nullptr) {
            return;
        }

        if (root->next[0]) {
            ClearRecursive(root->next[0]);
        }

        if (root->next[1]) {
            ClearRecursive(root->next[1]);
        }

        delete root;
    }

    Node* BuildRecursive(int* indices, int size, int depth)
    {
        if (size <= 0)
            return nullptr;

        const int axis = depth % PointType::DIM;    // 划分轴
        // const int mid = (size - 1) / 2;          // 划分值
        const int mid = size / 2;          // 划分值
        std::nth_element(indices, indices + mid, indices + size, [&](int lIdx, int rIdx) {
            return points_[lIdx][axis] < points_[rIdx][axis];
        });

        Node* node = new Node();
        node->idx = indices[mid];
        node->axis = axis;

        node->next[0] = BuildRecursive(indices, mid, depth + 1);
        node->next[1] = BuildRecursive(indices + mid + 1, size - mid - 1, depth + 1);

        return node;
    }

    Node* BuildRecursive(int* indices, int start, int end, int depth)
    {
        if (start >= end)
            return nullptr;

        const int axis = depth % PointType::DIM;    // 划分轴
        const int mid = (start + end) / 2;          // 划分值
        std::nth_element(indices + start, indices + mid, indices + end, [&](int l, int r) {
            return points_[l][axis] < points_[r][axis];
        });

        // debug
        for (int i = start; i < end; i++) {
            cout << indices[i] << " ";
        }
        cout << endl;
        for (int i = start; i < end; i++) {
            cout << "(";
            for (int j = 0; j < PointType::DIM; j++) {
                cout << points_[indices[i]][j] << ",";
            }
            cout << ")";
        }
        cout << endl;

        Node* node = new Node();
        node->idx = indices[mid];
        node->axis = axis;

        node->next[0] = BuildRecursive(indices, start, mid, axis + 1);
        node->next[1] = BuildRecursive(indices, mid + 1, end, axis + 1);

        return node;
    }
public:
    KDTree() : root_(nullptr)
    {}
    explicit KDTree(const std::vector<PointType>& points) : root_(nullptr)
    {
        Build(points);
    }
    ~KDTree()
    {
        Clear();
    }

    void Clear()
    {
        ClearRecursive(root_);
        root_ = nullptr;
        std::vector<PointType> points;
        points_.swap(points);
    }

    Node* Build(const std::vector<PointType>& points)
    {
        Clear();
        points_ = points;
        std::vector<int> indices(points.size());
        std::iota(indices.begin(), indices.end(), 0);
        root_ = BuildRecursive(indices.data(), points.size(), 0);
        // root_ = BuildRecursive(indices.data(), 0, points.size(), 0);

        return root_;
    }

    void preorder_traversal(Node* root);
    void inorder_traversal(Node* root);
};

template<typename PointType>
void KDTree<PointType>::preorder_traversal(Node* root)
{
    if (!root)
        return;

    cout << "(";
    for (int i = 0; i < PointType::DIM; i++) {
        cout << points_[root->idx][i] << ",";
    }
    cout << ")";
    preorder_traversal(root->next[0]);
    preorder_traversal(root->next[1]);
}

template<typename PointType>
void KDTree<PointType>::inorder_traversal(Node* root)
{
    if (!root)
        return;

    inorder_traversal(root->next[0]);
    cout << "(";
    for (int i = 0; i < PointType::DIM; i++) {
        cout << points_[root->idx][i] << ",";
    }
    cout << ")";
    inorder_traversal(root->next[1]);
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
    KDTree<Point> kdtree;
    Node* root = kdtree.Build(points);
    kdtree.preorder_traversal(root);   // 4 2 1 3 6 5 8
    putchar(10);
    cout << "-----------------------------------" << endl;
    kdtree.inorder_traversal(root);    // 1 2 3 4 5 6 8
    putchar(10);

    // 搜索最近点
    // Point query = {7.5};
    // Point query = {6.5};
    Point query = {5.5};
    // Point query = {4.5};

    // Point nearest = root->p;
    // float distance = std::numeric_limits<float>::max();
    // depth = 0;
    // nearestNeighborSearch(root, query, nearest, distance);
    // cout << "The nearest neighbor to query point is: (" << nearest.x[0] << ")" << endl;
    // for (auto& point : nearPoints) {
    //     for (int i = 0; i < k; i++) {
    //         cout << "(" << point.x[i] << ",";
    //     }
    //     cout << ")";
    // }
    // cout << endl;

    // for (auto& pt : nearPts) {
    //     cout << "dis:" << pt.first << "; ";
    //     for (int i = 0; i < k; i++) {
    //         cout << "(" << pt.second.x[i] << ",";
    //     }
    //     cout << ")" << endl;
    // }
    // cout << endl;

    kdtree.Clear();
}
#endif

#if 1
void test_two_dimensional_kd_tree()
{
    // 构建kd-tree
    // vector<std::array<float, 2>> points = {{2, 3}, {4, 7}, {5, 4}, {7, 2}, {8, 1}, {9, 6}};
    vector<Point> points = {{2, 3}, {4, 7}, {5, 4}, {7, 2}, {8, 1}, {9, 6}};

    // test
    // std::array<float, 2> arr = {2, 3};
    // Point pt;
    // pt.swap(arr);
    // cout << arr.size();
    // cout << pt.size() << endl;
    // for_each(arr.begin(), arr.end(), [](float x) {
    //     cout << x << " ";
    // });
    // cout << endl;
    // for_each(pt.begin(), pt.end(), [](float x) {
    //     cout << x << " ";
    // });
    // cout << endl;

    KDTree<Point> kdtree;
    kdtree.Build(points);

    Node* root = kdtree.root_;
    kdtree.inorder_traversal(root);    // (2,3), (5,4), (4,7), (7,2), (8,1), (9,6)
    putchar(10);

    // 搜索最近点
    // Point query = {2, 2};
    // Point query = {4.1, 4.1};
    // Point query = {2.1, 3.1};
    // Point query = {2, 4.5};

    // Point nearest;
    // float distance = FLOAT_MAX;
    // depth = 0;
    // nearestNeighborSearch(root, query, nearest, distance);
    // cout << "The nearest neighbor to query point is: (" << nearest.x[0] << "," << nearest.x[1] << ")" << endl;

    // for (auto& pt : nearPts) {
    //     cout << "dis:" << pt.first << "; (";
    //     for (int i = 0; i < k; i++) {
    //         cout << pt.second.x[i] << ",";
    //     }
    //     cout << ")" << endl;
    // }

    // 释放内存
    // kdtree.Clear();
}
#endif

int main()
{
    // std::vector<int> indices(10);
    // std::iota(indices.begin(), indices.end(), 0);

    // for (auto& i : indices) {
    //     cout << i << " ";
    // }
    // cout << endl;

    // test_one_dimensional_kd_tree();
    test_two_dimensional_kd_tree();
    return 0;
}