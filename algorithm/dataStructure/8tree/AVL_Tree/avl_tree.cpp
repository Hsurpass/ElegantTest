#include <iostream>
#include <stdio.h>

typedef struct AvlTreeNode
{
    int data;
    AvlTreeNode* left;
    AvlTreeNode* right;
    int height;
}AvlTreeNode;

AvlTreeNode* createNewNode(int data)
{
    AvlTreeNode* newNode = (AvlTreeNode*)malloc(sizeof(AvlTreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;

    return newNode;
}

int avlTreeHeight(AvlTreeNode* root)
{
    if(!root)
        return 0;

    int leftHeight = avlTreeHeight(root->left);
    int rightHeight = avlTreeHeight(root->right);
    
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int getBalanceFactor(AvlTreeNode* root)
{
    int leftH = avlTreeHeight(root->left);
    int rightH = avlTreeHeight(root->right);

    return leftH - rightH;
}


/*
    插入元素放在左子树的左节点(LL), 右旋
    root为最小不平衡子树(BF)的根节点
    最小不平衡子树的根节点是8(BF=2), 以8这个节点进行右旋
    返回调整完的根节点
                10                      10
              /     \                 /     \
            8        11             5        11
           /                       /  \
          5                       3    8
         /                       
        3                       

        对于avl树不可能出现这种情况，当3插入的时候就要进行调整了:
                10                
              /     \                 
            8        11                
           /                     
          5                      
         /  \                      
        3    4                   
*/
AvlTreeNode* rightRotation(AvlTreeNode* root)
{
    AvlTreeNode* pleft = root->left;
    root->left = pleft->right;
    pleft->right = root;

    root->height = avlTreeHeight(root);
    pleft->height = avlTreeHeight(pleft);

    return pleft;
}

/*
    插入元素放在右子树的右节点(RR), 左旋
    root为最小不平衡子树(BF)的根节点
    最小不平衡子树的根节点是11(BF=2), 以11这个节点进行左旋
    返回调整完的根节点
                10                      10
              /     \                 /     \
             8       11              8       14
                       \                    /   \
                        14                 11    15
                          \       
                          15     

        对于avl树不可能出现这种情况，当15插入的时候就要进行调整了:
                10           
              /     \        
             8       11      
                       \     
                        14   
                       /  \  
                      13   15                  
*/
AvlTreeNode* leftRotation(AvlTreeNode* root)
{
    AvlTreeNode* pright = root->right;
    root->right = pright->left;
    pright->left = root;

    root->height = avlTreeHeight(root);
    pright->height = avlTreeHeight(pright);

    return pright;
}

/*
    插入元素放在右子树的左节点(RL), 右左旋
    root为最小不平衡子树(BF)的根节点
    最小不平衡子树的根节点是11(BF=2), 以14这个节点进行右旋, 以11这个节点进行左旋
    返回调整完的根节点
                10                         10                           10
              /     \        14 右旋     /     \            11 右旋    /    \
             8       11       --->      8      11           ----->    8     15
            /          \               /         \                   /     /  \
           6            14            6          15                 6     11   14
                       /                           \
                      15                            14 
           
*/
AvlTreeNode* rightLeftRotation(AvlTreeNode* root)
{
    root->right = rightRotation(root->right);
    return leftRotation(root);
}

/*
    插入元素放在左子树的右节点(LL), 左右旋
    root为最小不平衡子树(BF)的根节点
    最小不平衡子树的根节点是8(BF=2), 先以5这个节点进行左旋, 再以8这个节点进行右旋
    返回调整完的根节点
                10                        10                    10
              /     \       5 左旋      /     \               /     \   
            8        11     ---->      8      11  ----->     6      11
           /                          /                    /   \
          5                          6                    5     8
           \                        /
            6                      5           
*/
AvlTreeNode* leftRightRotation(AvlTreeNode* root)
{
    root->left = leftRotation(root->left);
    return rightRotation(root);
}

/*
        6    6     6         6
       /    /       \         \
      4    4         8         8
     /      \         \        /
    2        5         9      7

*/
AvlTreeNode* insertAvlTreeNode_recursive(AvlTreeNode* root, int newVal)
{
    if(root == NULL)
    {
        return createNewNode(newVal);
    }
    else if(newVal < root->data)
    {
        root->left = insertAvlTreeNode_recursive(root->left, newVal);
        
        if (getBalanceFactor(root) == 2 )
        {
            if (newVal < root->left->data)  // LL 左子树左节点 右旋
            {
                root = rightRotation(root);
            }
            else if(newVal > root->left->data)  // LR 左子树右节点 左右旋
            {
                root = leftRightRotation(root);
            }
            
        }
        
    }
    else
    {
        root->right = insertAvlTreeNode_recursive(root->right, newVal);

        if (getBalanceFactor(root) == -2 )
        {
            if (newVal < root->right->data)  // RL 右子树左节点 右左旋
            {
                root = rightLeftRotation(root);
            }
            else if(newVal > root->right->data)  // RR 右子树右节点 左旋
            {
                root = leftRotation(root);
            }
        }
    }

    root->height = avlTreeHeight(root);

    return root;
}

void preOrderTraverseAvl(AvlTreeNode *root)
{
    if (root)
    {
        printf("%d ", root->data);
        preOrderTraverseAvl(root->left);
        preOrderTraverseAvl(root->right);
    }

}

void inOrderTraverseAvl(AvlTreeNode *root)
{
    if (root)
    {
        inOrderTraverseAvl(root->left);
        printf("%d ", root->data);
        inOrderTraverseAvl(root->right);
    }
}

void postOrderTraverseAvl(AvlTreeNode *root)
{
    if (root)
    {
        postOrderTraverseAvl(root->left);
        postOrderTraverseAvl(root->right);
        printf("%d ", root->data);
    }
}

int main()
{

    return 0;
}

