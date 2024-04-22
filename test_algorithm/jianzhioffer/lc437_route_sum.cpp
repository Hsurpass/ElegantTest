#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <stdlib.h>

using namespace std;

/*
leetcode 437
给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。

路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

示例1：
                            10
                          5    -3
                        3   2     11
                      3 -2 n  1     
输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
输出：3
解释：和等于 8 的路径有 3 条，如图所示。


示例 2：
                             5
                          4     8
                        11    13   4
                      7   2       5  1
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：3


*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr)
    {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr)
    {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right)
    {}
};

int cal_count(int targetSum, vector<TreeNode*>& v)
{
    int count = 0;
    int tmp = 0;
    for (vector<TreeNode*>::reverse_iterator itr = v.rbegin(); itr != v.rend(); itr++) {
        tmp += (*itr)->val;
        if (tmp == targetSum) {
            count++;
        }
    }
    v.pop_back();

    return count;
}

int path_sum(TreeNode* root, int targetSum, vector<TreeNode*>& v)
{
    if (root == nullptr)
        return 0;
    int count = 0;
    v.push_back(root);
    count += path_sum(root->left, targetSum, v);
    count += path_sum(root->right, targetSum, v);
    count += cal_count(targetSum, v);
    return count;
}

class Solution
{
public:
    Solution() : m_count(0)
    {}
/*
                            10
                          5    -3
                        3   2     11
                      3 -2 n  1     
*/
    // int cal_count(vector<TreeNode*>& v, int targetSum)
    void cal_count(int targetSum)
    {
        int tmp = 0;
        for (vector<TreeNode*>::reverse_iterator itr = m_v.rbegin(); itr != m_v.rend(); itr++) {
            tmp += (*itr)->val;
            if (tmp == targetSum) {
                m_count++;
            }
        }
    }

    void pathSum(TreeNode* root, int targetSum)
    {
        if (root == nullptr)
            return;

        m_v.push_back(root);
        pathSum(root->left, targetSum);
        pathSum(root->right, targetSum);
        cal_count(targetSum);
        m_v.pop_back();
    }

    int get_count()
    {
        return m_count;
    }

private:
    int m_count;
    vector<TreeNode*> m_v;
};

TreeNode* construct_binaryTree(const vector<string>& arr)
{
    if (arr.empty())
        return nullptr;
    TreeNode* root = new TreeNode(atoi(arr[0].c_str()));
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;
    int size = arr.size();
    while (i < size) {
        TreeNode* t = q.front();
        q.pop();
        if (arr[i] != "null") {
            t->left = new TreeNode(atoi(arr[i].c_str()));
            q.push(t->left);
        }
        ++i;
        if (i < size && arr[i] != "null") {
            t->right = new TreeNode(atoi(arr[i].c_str()));
            q.push(t->right);
        }
        ++i;
    }

    return root;
}

void destroy_binaryTree(TreeNode* root)
{
    if (!root)
        return;

    destroy_binaryTree(root->left);
    destroy_binaryTree(root->right);

    delete root;
    root = nullptr;
}

void print_midorder_binaryTree(TreeNode* root)
{
    if (!root)
        return;
    print_midorder_binaryTree(root->left);
    cout << root->val << " ";
    print_midorder_binaryTree(root->right);
}

void print_preorder_binaryTree(TreeNode* root)
{
    if (!root)
        return;
    cout << root->val << " ";
    print_preorder_binaryTree(root->left);
    print_preorder_binaryTree(root->right);
}

/*
                            10
                          5    -3
                        3   2     11
                      3 -2 n  1     
pre: 10 5 3 3 -2 2 1 -3 11
mid: 3 3 -2 5 2 1 10 -3 11
3 5
1 2 5
11 -3
*/
void test1()
{
    vector<string> arr = {"10", "5", "-3", "3", "2", "null", "11", "3", "-2", "null", "1"};
    TreeNode* root = construct_binaryTree(arr);

    print_preorder_binaryTree(root);
    cout << endl;
    print_midorder_binaryTree(root);
    cout << endl;

    Solution s;
    s.pathSum(root, 8);
    cout << s.get_count() << endl;  // 3

    destroy_binaryTree(root);
}

/*
示例 2：
                             5
                          4     8
                        11    13   4
                      7   2       5  1
preorder: 5 4 11 7 2 8 13 4 5 1
midorder: 7 11 2 4 5 13 8 5 4 1
7 11 4
2 11 4 5
5 4 8 5
*/
void test2()
{
    vector<string> arr = {"5", "4", "8", "11", "null", "13", "4", "7", "2", "null", "null", "5", "1"};
    TreeNode* root = construct_binaryTree(arr);

    print_preorder_binaryTree(root);
    cout << endl;
    print_midorder_binaryTree(root);
    cout << endl;

    Solution s;
    s.pathSum(root, 22);
    cout << s.get_count() << endl;

    destroy_binaryTree(root);
}

/*
                            10
                          5    -3
                        3   2     11
                      3 -2 n  1     
pre: 10 5 3 3 -2 2 1 -3 11
mid: 3 3 -2 5 2 1 10 -3 11
3 5
1 2 5
11 -3
*/
void test_c1()
{
    vector<string> arr = {"10", "5", "-3", "3", "2", "null", "11", "3", "-2", "null", "1"};
    TreeNode* root = construct_binaryTree(arr);

    print_preorder_binaryTree(root);
    cout << endl;
    print_midorder_binaryTree(root);
    cout << endl;

    vector<TreeNode*> v;
    int count = path_sum(root, 8, v);
    cout << "count: " << count << endl;

    destroy_binaryTree(root);
}

/*
示例 2：
                             5
                          4     8
                        11    13   4
                      7   2       5  1
preorder: 5 4 11 7 2 8 13 4 5 1
midorder: 7 11 2 4 5 13 8 5 4 1
2 11 
1 3
1 4 8
8 5
*/
void test_c2()
{
    vector<string> arr = {"5", "4", "8", "11", "null", "13", "4", "7", "2", "null", "null", "5", "1"};
    TreeNode* root = construct_binaryTree(arr);

    print_preorder_binaryTree(root);
    cout << endl;
    print_midorder_binaryTree(root);
    cout << endl;

    vector<TreeNode*> v;
    int count = path_sum(root, 13, v);
    cout << "count: " << count << endl; // 4

    destroy_binaryTree(root);
}

int main()
{
    // test1();
    // test2();

    test_c1();
    test_c2();

    return 0;
}