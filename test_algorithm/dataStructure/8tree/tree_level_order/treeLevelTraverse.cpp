#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
    TreeNode(int d):data(d), left(NULL), right(NULL){}
    int data;
    TreeNode* left;
    TreeNode* right;
};

void levelTraverse(TreeNode* root)
{
    if (!root)
        return;

    std::queue<TreeNode*> q;
    q.push(root);
    queue<TreeNode*> v;

    while(!q.empty() || !v.empty())
    {
        if(q.empty())
        {
            q.swap(v);
            putchar(10);
            cout << "--------------------" << endl;
        }

        TreeNode* node = q.front();
        cout << node->data << " ";

        
        if(node->left)
        {
            v.push(node->left);
        }
        if(node->right)
        {
            v.push(node->right);
        }
        q.pop();
    }    
    putchar(10);
}

void test_level_traverse()
{
    TreeNode node1(1);
    TreeNode node2(2);
    TreeNode node3(3);
    TreeNode node4(4);
    TreeNode node5(5);

    node1.left = &node2;
    node1.right = &node3;
    node2.left = &node4;
    node2.right = &node5;

    levelTraverse(&node1);
}

int main()
{
    test_level_traverse();
}