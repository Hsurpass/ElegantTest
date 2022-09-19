#include <stdio.h>

typedef struct _TreeNode
{
    int _data;
    struct _TreeNode *_left;
    struct _TreeNode *_right;
}TreeNode;

void preordertraverse(TreeNode *root)
{
    if(root != NULL)    // 递归结束条件
    {
        printf("%d ",root->_data);
        preordertraverse(root->_left);
        preordertraverse(root->_right);
    }
}

void inordertraverse(TreeNode *root)
{
    if(root != NULL)    // 递归结束条件
    {
        inordertraverse(root->_left);
        printf("%d ",root->_data);
        inordertraverse(root->_right);
    }
}
void postordertraverse(TreeNode *root)
{
    if(root != NULL)    // 递归结束条件
    {
        postordertraverse(root->_left);

        postordertraverse(root->_right);
        printf("%d ",root->_data);
    }
}

/*
           1a
          /   \
        2b      3c
        / \       \
       4d 5e      6f
*/
int main()
{
    TreeNode a,b,c,d,e,f;
    TreeNode * root = &a;
    a._data = 1;
    b._data = 2;c._data = 3;
    d._data = 4;e._data = 5;f._data = 6;
    a._left = &b;
    a._right = &c;
    b._left = &d;
    b._right = &e;
    c._left = NULL;c._right = &f;
    d._left = d._right = NULL;
    e._left = e._right = NULL;
    f._left = f._right = NULL;

    preordertraverse(root); //1 2 4 5 3 6
    putchar(10);
    inordertraverse(root);//4 2 5 1 3 6
    putchar(10);
    postordertraverse(root);//4 5 2 6 3 1
    putchar(10);

    return 0;
}
