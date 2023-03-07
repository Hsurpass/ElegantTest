#include <iostream>
#include <stack>
#include <stdio.h>
#include "stack_list_c.h"

using namespace std;
//typedef struct _TreeNode
//{
//    int _data;
//    struct _TreeNode *_left;
//    struct _TreeNode *_right;
//}TreeNode;

void preOrderIteratorNew(TreeNode *root)
{
    if (!root)
        return;

    std::stack<TreeNode *> st;
    st.push(root);

    while (!st.empty())
    {
        TreeNode *node = st.top();
        printf("%d ", node->_data);
        st.pop();

        //  先压right, 后压left
        if (node->_right)
        {
            st.push(node->_right);
        }
        if (node->_left)
        {
            st.push(node->_left);
        }
    }
    putchar(10);
}

void preOrderIteratorWithStack01(TreeNode *root)
{
    if (root == NULL)
        return;

    std::stack<TreeNode *> st;
    printf("data:%d ", root->_data);
    st.push(root);  
    root = root->_left;

    while (root || !st.empty())   // 对root要进行判断，防止在弹出根节点时栈为空而root不为空
    {
        while (root)    // 左孩子一直入栈
        {
            printf("data:%d ", root->_data);    // 在入栈之前访问元素，正好是先访问根节点
            st.push(root);
            root = root->_left;
        }

        TreeNode *top = st.top();
        root = top->_right;
        st.pop();
    }
    putchar(10);
}

void preOrderIteratorWithStack(TreeNode *root)
{
    if (root == NULL)
        return;

    std::stack<TreeNode *> st;

    while (root || !st.empty())// 对root要进行判断，防止在弹出根节点时栈为空而root不为空
    {
        while (root)    // 左孩子一直入栈
        {
            printf("data:%d ", root->_data);    // 在入栈之前访问元素，正好是先访问根节点
            st.push(root);
            root = root->_left;
        }

        TreeNode *top = st.top();
        root = top->_right;
        st.pop();
    }
    putchar(10);
}

void inOrderIteratorWithStack(TreeNode *root)
{
    if (root == NULL)
        return;

    std::stack<TreeNode *> st;
    // st.push(root);

    while (root || !st.empty())
    {
        while (root)    // 左孩子一直入栈
        {
            st.push(root);
            root = root->_left;
        }

        if (!st.empty()) // 需要判空，如果是单边树访问数据会崩
        {
            TreeNode *top = st.top();
            printf("data:%d ", top->_data); // 左孩子出栈的时候访问
            root = top->_right;
            st.pop();
        }
    }
    putchar(10);
}

void postOrderIteratorWithStack(TreeNode *root)
{
    if (root == NULL)
        return;

    std::stack<TreeNode *> st;
    st.push(root);
    TreeNode *pre = NULL;

    while (!st.empty())
    {
        TreeNode *cur = st.top();
        if ((cur->_left == NULL && cur->_right == NULL) || 
            ((pre != NULL) && (pre == cur->_left || pre == cur->_right))
            )
        {
            printf("data:%d ", cur->_data);
            st.pop();
            pre = cur;
        }
        else
        {
            if (cur->_right)
            {
                st.push(cur->_right);
            }
            if (cur->_left)
            {
                st.push(cur->_left);
            }
        }
    }
    putchar(10);
}

void preorderiteration(TreeNode *r)
{
    if (r != NULL)
    {
        Stacklist sl;
        initStacklist(&sl);
        while (r || !isempty(&sl))
        {
            while (r)
            {
                printf("%d ", r->_data);
                push(&sl, r);
                r = r->_left;
            }
            r = pop(&sl);
            r = r->_right;
        }
        putchar(10);
    }
}

void inorderiteration(TreeNode *r)
{
    if (r)
    {
        Stacklist sl;
        initStacklist(&sl);
        while (r || !isempty(&sl))
        {
            while (r)
            {
                push(&sl, r);
                r = r->_left;
            }

            if (!isempty(&sl)) // 需要判空，如果是单边树访问数据会崩
            {
                r = pop(&sl);
                printf("%d ", r->_data); //4 2 5 1 3 6
                r = r->_right;
            }
        }
        putchar(10);
    }
}

int gethightoftree(TreeNode *root)
{
    int lh, rh, maxh;
    if (root) // 递归结束条件
    {
        lh = gethightoftree(root->_left);
        rh = gethightoftree(root->_right);
        maxh = (lh > rh) ? lh : rh;
        return maxh + 1;
    }
    else
    {
        return 0;
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
    TreeNode a, b, c, d, e, f;
    TreeNode *root = &a;
    a._data = 1;
    b._data = 2;
    c._data = 3;
    d._data = 4;
    e._data = 5;
    f._data = 6;

    a._left = &b;
    a._right = &c;
    b._left = &d;
    b._right = &e;
    c._left = NULL;
    c._right = &f;
    d._left = d._right = NULL;
    e._left = e._right = NULL;
    f._left = f._right = NULL;

    // preorderiteration(root); // 1 2 4 5 3 6
    // inorderiteration(root);  // 4 2 5 1 3 6

    // preOrderIteratorWithStack(root);
    // inOrderIteratorWithStack(root);
    // postOrderIteratorWithStack(root);    // 4 5 2 6 3 1

    // preOrderIteratorNew(root);
    
    preOrderIteratorWithStack01(root);

    // printf("hight of tree = %d\n", gethightoftree(root));
    return 0;
}
