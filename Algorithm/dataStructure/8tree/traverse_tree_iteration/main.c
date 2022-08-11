#include <stdio.h>
#include "stack_list_c.h"


//typedef struct _TreeNode
//{
//    int _data;
//    struct _TreeNode *_left;
//    struct _TreeNode *_right;
//}TreeNode;

void preorderiteration(TreeNode *r)
{
    if(r != NULL)
    {
        Stacklist sl;
        initStacklist(&sl);
        while (r || !isempty(&sl))
        {
            while (r) {
                printf("%d ",r->_data);
                push(&sl,r);
                r = r->_left;
            }
            r = pop(&sl);
            r = r->_right;
        }
    }
}
void inorderiteration(TreeNode *r)
{
    if(r)
    {
        Stacklist sl;
        initStacklist(&sl);
        while (r || !isempty(&sl)) {
            while (r) {
                push(&sl,r);
                r = r->_left;
            }
            r = pop(&sl);
            printf("%d ",r->_data);//4 2 5 1 3 6
            r = r->_right;
        }
    }
}
int gethightoftree(TreeNode* root)
{
    int lh,rh,maxh;
    if(root)
    {
        lh = gethightoftree(root->_left);
        rh = gethightoftree(root->_right);
        maxh = (lh>rh)?lh:rh;
        return maxh+1;
    }
    else {
        return 0;
    }
}
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

    preorderiteration(root);//1 2 4 5 3 6
    putchar(10);
    inorderiteration(root);
    putchar(10);

    printf("hight of tree = %d\n",gethightoftree(root));
    return 0;
}
