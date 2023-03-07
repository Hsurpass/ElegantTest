#include <stdio.h>
#include <stdlib.h>

typedef struct _TreeNode
{
    int _data;
    struct _TreeNode *_left;
    struct _TreeNode *_right;
} TreeNode;

void insertBST_iteration(TreeNode **r, int data)
{
    TreeNode *t = *r;
    if (*r == NULL)
    {
        *r = (TreeNode *)malloc(sizeof(TreeNode));
        (*r)->_data = data;
        (*r)->_left = (*r)->_right = NULL;
    }
    else
    {
        while (1)
        {
            if (data > t->_data)
            {
                if (t->_right == NULL)
                {
                    TreeNode *cur = (TreeNode *)malloc(sizeof(TreeNode));
                    cur->_data = data;
                    cur->_left = cur->_right = NULL;
                    t->_right = cur;
                    break;
                }
                t = t->_right;
            }
            else
            {
                if (t->_left == NULL)
                {
                    TreeNode *cur = (TreeNode *)malloc(sizeof(TreeNode));
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
void insertBST_recursive(TreeNode **r, int data)
{
    TreeNode *t = *r;
    if (*r == NULL)
    {
        *r = (TreeNode *)malloc(sizeof(TreeNode *));
        (*r)->_data = data;
        (*r)->_left = (*r)->_right = NULL;
    }
    else
    {
        if (data > t->_data)
        {
            insertBST_recursive(&t->_right, data);
        }
        else
        {
            insertBST_recursive(&t->_left, data);
        }
    }
}

TreeNode* newNode(int data)
{
    TreeNode* newNode = (TreeNode *)malloc(sizeof(TreeNode *));
    newNode->_data = data;
    newNode->_left = newNode->_right = NULL;
}

TreeNode* insertBST_recursive_NEW(TreeNode *root, int data)
{
    if (!root)
    {
        return newNode(data);
    }

    if (data < root->_data)
    {
        root->_left = insertBST_recursive_NEW(root->_left, data);
    }
    else    // >=
    {
        root->_right = insertBST_recursive_NEW(root->_right, data);
    }
    
    return root;
}

TreeNode *searchBST_iteration(TreeNode *root, int data)
{
    while (root)
    {
        if (root->_data == data)
        {
            return root;
        }
        else if (data > root->_data)
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

TreeNode *searchBST_recursive(TreeNode *root, int data)
{
    if (!root)
        return NULL;

    if (root->_data == data)
    {
        return root;
    }
    else if (data > root->_data)
    {
        return searchBST_recursive(root->_right, data);
    }
    else
    {
        return searchBST_recursive(root->_left, data);
    }
}

TreeNode *getMinNodeOfBstTree(TreeNode *root)
{
    while (root->_left)
    {
        root = root->_left;
    }

    return root;
}

TreeNode *getMaxNodeOfBstTree(TreeNode *root)
{
    while (root->_right)
    {
        root = root->_right;
    }

    return root;
}

TreeNode *getParentNodeOfBst(TreeNode *root, int val)
{
    static TreeNode *parent = NULL;//递归中的静态变量

    if (root)
    {
        if ( (root->_left && root->_left->_data == val) || 
             (root->_right && root->_right->_data == val)
           )
            parent = root;

        getParentNodeOfBst(root->_left, val);
        getParentNodeOfBst(root->_right, val);
    }

    return parent;
}

TreeNode *getParentNodeOfBst_new(TreeNode *root, int val)
{
    if (!root)
        return NULL;
    
    if ( (root->_left && root->_left->_data == val) || 
             (root->_right && root->_right->_data == val)
           )
    {
        return root;
    }

    if (root->_data < val)
    {
        return getParentNodeOfBst_new(root->_right, val);
    }
    else
    {
        return getParentNodeOfBst_new(root->_left, val);
    }
}

/*
    BST节点的删除有三种情况：
        没有子节点: 直接删除
        有一个子节点: 被删除节点的父节点指向被删除节点的左孩子或右孩子
        有两个子节点: 1.先找到被删节点的右子树的最小节点。
                     2.把最小节点的值赋值给被删节点。
                     3.再去删除右子树的最小值节点。
*/
TreeNode* deleteNodeOfBST_recursive(TreeNode* root, int val)
{
    if (!root)          // 空树或者没有找到要删除的节点
        return root;
    
    if (val < root->_data)  // 要删除的节点在左子树
    {
        root->_left = deleteNodeOfBST_recursive(root->_left, val);
    }
    else if(val > root->_data)  // 要删除的节点在右子树
    {
        root->_right = deleteNodeOfBST_recursive(root->_right, val);
    }
    else    // 找到了要删除的节点
    {
        if (root->_left == NULL)    // 只有一个节点或者无节点
        {
            TreeNode* tmpNode = root->_right;
            free(root);
            return tmpNode;
        }
        else if(root->_right == NULL)   // 只有一个节点或者无节点
        {
            TreeNode* tmpNode = root->_left;
            free(root);
            return tmpNode;
        }
        else    // 两个子节点
        {
            TreeNode* minNodeOfRightTree = getMinNodeOfBstTree(root->_right);   // 找到右子树的最小节点(中序遍历的第一个)
            root->_data = minNodeOfRightTree->_data;
            root->_right = deleteNodeOfBST_recursive(root->_right, minNodeOfRightTree->_data);  // 删除右子树的最小子节点
        }

    }
    
    return root;
}

void destroyBst(TreeNode* root)
{
    if (root)
    {
        destroyBst(root->_left);
        destroyBst(root->_right);
        free(root);
    }
    
}

void preOrderTraverseBst(TreeNode *root)
{
    if (root)
    {
        printf("%d ", root->_data);
        preOrderTraverseBst(root->_left);
        preOrderTraverseBst(root->_right);
    }

}

void inOrderTraverseBst(TreeNode *root)
{
    if (root)
    {
        inOrderTraverseBst(root->_left);
        printf("%d ", root->_data);
        inOrderTraverseBst(root->_right);
    }
}

void postOrderTraverseBst(TreeNode *root)
{
    if (root)
    {
        postOrderTraverseBst(root->_left);
        postOrderTraverseBst(root->_right);
        printf("%d ", root->_data);
    }
}

/*
            31
        9       40
          16        200

    pre:  31 9 16 40 200
    in:   9 16 31 40 200
    post: 16 9 200 40 31
*/
int main()
{
    TreeNode *root = NULL;
    // insertBST_iteration(&root,30);
    // insertBST_iteration(&root,8);
    // insertBST_iteration(&root,15);
    // insertBST_iteration(&root,36);
    // insertBST_iteration(&root,100);

    // insertBST_recursive(&root, 31);
    // insertBST_recursive(&root, 9);
    // insertBST_recursive(&root, 16);
    // insertBST_recursive(&root, 40);
    // insertBST_recursive(&root, 200);

    root = insertBST_recursive_NEW(root, 31);
    insertBST_recursive_NEW(root, 9);
    insertBST_recursive_NEW(root, 16);
    insertBST_recursive_NEW(root, 40);
    insertBST_recursive_NEW(root, 200);

    preOrderTraverseBst(root);  // pre:  31 9 16 40 200
    putchar(10);
    inOrderTraverseBst(root);   // in:   9 16 31 40 200
    putchar(10);
    postOrderTraverseBst(root); // post: 16 9 200 40 31
    putchar(10);

    // TreeNode *r = searchBST_iteration(root, 40);
    TreeNode *r = searchBST_recursive(root, 40);
    if (r)
    {
        printf("find: %d\n", r->_data);
    }
    else
    {
        printf("find none\n");
    }

    TreeNode *minNode = getMinNodeOfBstTree(root);
    printf("minNode->data:%d\n", minNode->_data);

    TreeNode *maxNode = getMaxNodeOfBstTree(root);
    printf("maxNode->data:%d\n", maxNode->_data);

    // TreeNode* parentNode = getParentNodeOfBst(root, 300);
    TreeNode* parentNode = getParentNodeOfBst_new(root, 16);
    if (parentNode)
    {
        printf("parentNode->data:%d\n", parentNode->_data);
    }
    else
    {
        printf("parent node is NULL\n");
    }

    TreeNode* t = deleteNodeOfBST_recursive(root, 9);
    printf("t->data:%d\n", t->_data);
    inOrderTraverseBst(t);
    putchar(10);

    destroyBst(root);
    
    return 0;
}
