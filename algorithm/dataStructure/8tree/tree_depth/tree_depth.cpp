#include <iostream>
#include <stdio.h>

// using namespace std;

typedef struct _TreeNode
{
    int _data;
    struct _TreeNode *_left;
    struct _TreeNode *_right;
} TreeNode;

int tree_depth(TreeNode *root)
{
    if (root == NULL)
        return 0;

    int leftDepth, rightDepth;
    leftDepth = tree_depth(root->_left);
    rightDepth = tree_depth(root->_right);

    return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
}

/*
           1a
          /   \
        2b      3c
       /  \       \
      4d  5e      6f
          /
         7g 
*/
int main()
{
    TreeNode a, b, c, d, e, f, g;
    TreeNode *root = &a;
    a._data = 1;
    b._data = 2;
    c._data = 3;
    d._data = 4;
    e._data = 5;
    f._data = 6;
    g._data = 7;

    a._left = &b; a._right = &c;
    // a._left = a._right = NULL;
    b._left = &d; b._right = &e;
    c._left = NULL; c._right = &f;
    d._left = d._right = NULL;
    e._left = &g; e._right = NULL;
    f._left = f._right = NULL;
    g._left = g._right = NULL;

    int depth = tree_depth(root); // 4
    printf("tree depth:%d\n", depth);

    return 0;
}