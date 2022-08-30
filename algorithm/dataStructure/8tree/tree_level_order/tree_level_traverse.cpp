#include <iostream>
#include <queue>
#include <stdio.h>
#include "queuelist_c.h"

void tree_level_traverse_with_queuelist(TreeNode* root)
{
    PQueue pq;
    queueinit(&pq);
    enqueue(&pq, root);

    while (!isqueueempty(&pq))
    {
        TreeNode *ptreedata = dequeue(&pq);
        printf("%c ", ptreedata->_data);

        if (ptreedata->_left != NULL)
        {
            enqueue(&pq, ptreedata->_left);
        }
        if (ptreedata->_right != NULL)
        {
            enqueue(&pq, ptreedata->_right);
        }
    }
    putchar(10);
}

void tree_level_traverse_with_stlqueue(TreeNode* root)
{
    std::queue<TreeNode*> pqt;

    pqt.push(root);
    while (!pqt.empty())
    {
        TreeNode* node = pqt.front();
        printf("%c ", node->_data);

        if (node->_left)
        {
            pqt.push(node->_left);
        }
        if (node->_right)
        {
            pqt.push(node->_right);
        }

        pqt.pop();
    }

    putchar(10);
}

int main()
{
    TreeNode a, b, c, d, f, j, k;
    TreeNode *root = &a;
    a._data = 'A';
    b._data = 'B';
    c._data = 'C';
    d._data = 'D';
    f._data = 'F';
    j._data = 'J';
    k._data = 'K';

    a._left = &b;
    a._right = &c;
    b._left = &d;
    b._right = NULL;
    d._left = d._right = NULL;
    c._left = &f;
    c._right = NULL;
    f._left = &j;
    f._right = &k;
    j._left = j._right = k._left = k._right = NULL;

    // tree_level_traverse_with_queuelist(root);
    tree_level_traverse_with_stlqueue(root);

    return 0;
}
