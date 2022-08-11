#include <stdio.h>
#include"queuelist_c.h"


int main()
{
    TreeNode a,b,c,d,f,j,k;
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

    PQueue pq;
    queueinit(&pq);
    enqueue(&pq,root);

    while (!isqueueempty(&pq)) {
        TreeNode* ptreedata = dequeue(&pq);
        printf("%c ",ptreedata->_data);

        if(ptreedata->_left != NULL)
        {
            enqueue(&pq,ptreedata->_left);
        }
        if(ptreedata->_right != NULL)
        {
            enqueue(&pq,ptreedata->_right);
        }
    }

    return 0;
}
