#include <iostream>
#include <stack>

using namespace std;

typedef struct _TreeNode
{
    int _data;
    struct _TreeNode *_left;
    struct _TreeNode *_right;
}TreeNode;

/*
           1a
          /   \
        2b      3c
        / \    /  \
       4d 5e  6f  7g

            1a
          /   \
        3c     2b
        / \    /  \
       7g 6f  5e  4d
*/

TreeNode* binaryTree_invert(TreeNode* root)
{
    if (!root)
        return nullptr;
        
    TreeNode* tmp = root->_left;
    root->_left = root->_right;
    root->_right = tmp;

    binaryTree_invert(root->_left);
    binaryTree_invert(root->_right);

    return root;
}

TreeNode* binaryTree_invert_iteration(TreeNode* root)
{
    stack<TreeNode*> st;
    st.push(root);

    while (!st.empty() )
    {
        TreeNode* currNode = st.top();
        st.pop();

        TreeNode* tmp = currNode->_left;
        currNode->_left = currNode->_right;
        currNode->_right = tmp;

        if(currNode->_left != NULL )
            st.push(currNode->_left);
        if(currNode->_right != NULL)
            st.push(currNode->_right);
    }
    
    return root;
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

int main()
{
    TreeNode a,b,c,d,e,f,g;
    TreeNode* root = &a;
    a._data = 1;b._data = 2;c._data = 3;
    d._data = 4;e._data = 5;f._data = 6; g._data = 7;

    a._left = &b; a._right = &c;
    b._left = &d; b._right = &e;
    c._left = &f; c._right = &g;
    d._left = d._right = NULL;
    e._left = e._right = NULL;
    f._left = f._right = NULL;
    g._left = g._right = NULL;

    // root = binaryTree_invert(root);
    root = binaryTree_invert_iteration(root);

    inordertraverse(root);
    putchar(10);

    return 0;
}