#include <cstdio>
#include <iostream>

using namespace std;

typedef struct _TreeNode
{
    int _data;
    struct _TreeNode* _left;
    struct _TreeNode* _right;
} TreeNode;

void reverse_binarytree(TreeNode* root)
{
    if (root == nullptr) {
        return;
    }

    TreeNode* tmp = root->_left;
    root->_left = root->_right;
    root->_right = tmp;
    reverse_binarytree(root->_left);
    reverse_binarytree(root->_right);
}

void inordertraverse(TreeNode* root)
{
    if (root != NULL)    // 递归结束条件
    {
        inordertraverse(root->_left);
        printf("%d ", root->_data);
        inordertraverse(root->_right);
    }
}

/*
        1                   1
    2       3            3     2
  4  5     6 7          7 6   5 4
*/
void test_reverse_tree()
{
    TreeNode a, b, c, d, e, f, g;
    TreeNode* root = &a;
    a._data = 1;
    b._data = 2;
    c._data = 3;
    d._data = 4;
    e._data = 5;
    f._data = 6;
    g._data = 7;

    a._left = &b;
    a._right = &c;
    b._left = &d;
    b._right = &e;
    c._left = &f;
    c._right = &g;
    d._left = d._right = NULL;
    e._left = e._right = NULL;
    f._left = f._right = NULL;
    g._left = g._right = NULL;

    inordertraverse(root);  // 4 2 5 1 6 3 7
    putchar(10);
    reverse_binarytree(root);
    inordertraverse(root);  // 7 3 6 1 5 2 4
    putchar(10);
}

int main()
{
    test_reverse_tree();

    return 0;
}