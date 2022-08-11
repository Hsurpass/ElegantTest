#include <stdio.h>
#include <stdlib.h>

typedef struct _TreeNode
{
    int _data;
    struct _TreeNode *_left;
    struct _TreeNode *_right;
}TreeNode;

void insertBST_iteration(TreeNode **r,int data)
{
    TreeNode *t = *r;
    if(*r == NULL)
    {
        *r = (TreeNode*)malloc(sizeof(TreeNode));
        (*r)->_data = data;
        (*r)->_left = (*r)->_right = NULL;
    }
    else {
        while (1) {
            if(data > t->_data)
            {
                if(t->_right == NULL)
                {
                    TreeNode *cur = (TreeNode*)malloc(sizeof(TreeNode));
                    cur->_data = data;
                    cur->_left = cur->_right = NULL;
                    t->_right = cur;
                    break;
                }
                t = t->_right;
            }
            else
            {
                if(t->_left == NULL)
                {
                    TreeNode *cur = (TreeNode*)malloc(sizeof(TreeNode));
                    cur->_data = data;
                    cur->_left = cur->_right = NULL;
                    t->_left = cur;
                    break;
                }
                t = t->_left;
            }
        }
    }
}
void insertBST_recursive(TreeNode** r,int data)
{
    TreeNode *t = *r;
    if(*r == NULL)
    {
        *r = (TreeNode*)malloc(sizeof(TreeNode*));
        (*r)->_data = data;
        (*r)->_left = (*r)->_right = NULL;
    }
    else {
        if(data>t->_data){
            insertBST_recursive(&t->_right,data);
        }
        else
        {
            insertBST_recursive(&t->_left,data);
        }
    }
}
TreeNode* searchBST_iteration(TreeNode* root,int data)
{
    while (root) {
        if(root->_data == data)
        {
            return root;
        }
        else if(data > root->_data)
        {
            root = root->_right;
        }
        else
        {
            root = root->_left;
        }
    }
    return NULL;
}
void inordertraverse(TreeNode* root)
{
    if(root)
    {
        inordertraverse(root->_left);
        printf("%d ",root->_data);
        inordertraverse(root->_right);
    }
}
int main()
{
    TreeNode *root = NULL;
//    insertBST_iteration(&root,30);
//    insertBST_iteration(&root,8);
//    insertBST_iteration(&root,15);
//    insertBST_iteration(&root,36);
//    insertBST_iteration(&root,100);

    insertBST_recursive(&root,31);
    insertBST_recursive(&root,9);
    insertBST_recursive(&root,16);
    insertBST_recursive(&root,40);
    insertBST_recursive(&root,200);

    inordertraverse(root);
    putchar(10);
    TreeNode* r = searchBST_iteration(root,40);
    if(r)
    {
        printf("find: %d\n",r->_data);
    }
    else {
        printf("find none\n");
    }

    return 0;
}
