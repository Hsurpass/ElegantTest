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
    newNode->height = 1;

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
    if (root == NULL)
        return 0;

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

AvlTreeNode* getMinNodeOfRightTree(AvlTreeNode* root)
{
    if (!root)
        return root;
    
    while (root->left)
    {
        root = root->left;
    }
    return root;
}

/*
    20            20   BF(root->left)>=0     20  BF(root->left)<0   20       20 BF(root->right)<=0  20     BF(root->right)>0
   /   \        /    \   BF(10)>=0          /  \    BF(10)<0       /  \     /  \     BF(30)<=0     /  \     BF(30)>0
  10    30     10    30 删除30, LL右旋     10   30  删除30, LR     10  30   10  30   删除10, RR    10   30  删除10, RL
  /           /  \                          \                           \      / \                    /  
 8           8   15                         15                          40    25 40                  25  

*/
AvlTreeNode* deleteNodeOfAvlTree_revursive(AvlTreeNode* root, int key)
{
    if(!root)
        return root;
    
    if(key < root->data)
    {
        root->left = deleteNodeOfAvlTree_revursive(root->left, key);
    }
    else if(key > root->data)
    {
        root->right = deleteNodeOfAvlTree_revursive(root->right, key);
    }
    else
    {
        if (root->left == NULL) // 只有一个节点或者无节点
        {
            AvlTreeNode* rightNode = root->right;
            return rightNode;
        }
        else if(root->right == NULL)    // 只有一个节点或者无节点
        {
            AvlTreeNode* leftNode = root->left;
            return leftNode;
        }
        else   // 有两个节点
        {
            AvlTreeNode* minNode = getMinNodeOfRightTree(root->right);
            root->data = minNode->data;
            root->right = deleteNodeOfAvlTree_revursive(root->right, key);
        }
    }

    root->height = avlTreeHeight(root); // 更新当前节点的树的高度
    int balanceFactor = getBalanceFactor(root);

    if(balanceFactor == 2)  // 左子树比右子树高
    {
        if (getBalanceFactor(root->left) >= 0 )   // root的左子树的的根节点的左子树插入元素导致失衡
        {
            return rightRotation(root);
        }
        else if (getBalanceFactor(root->left) < 0)
        {
            return leftRightRotation(root);
        }
    }
    else if (balanceFactor == -2)   // 右子树比左子树高
    {
         if (getBalanceFactor(root->right) > 0 )   // root的左子树的的根节点的左子树插入元素导致失衡
        {
            return rightLeftRotation(root);
        }
        else if (getBalanceFactor(root->left) <= 0)
        {
            return leftRotation(root);
        }
    }
    
    
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

void deleteAvlNodeLL()
{
    AvlTreeNode* root = NULL;
    root = insertAvlTreeNode_recursive(root, 10);
    root = insertAvlTreeNode_recursive(root, 20);
    root = insertAvlTreeNode_recursive(root, 30);
    root = insertAvlTreeNode_recursive(root, 8);
    preOrderTraverseAvl(root);  // 20 10 8 30
    putchar(10);
    inOrderTraverseAvl(root);   // 8 10 20 30
    putchar(10);

    root = deleteNodeOfAvlTree_revursive(root, 30);
    preOrderTraverseAvl(root);  // 10 8 20
    putchar(10);
    inOrderTraverseAvl(root);   // 8 10 20
    putchar(10);
}

void deleteAvlNodeLR()
{
    AvlTreeNode* root = NULL;
    root = insertAvlTreeNode_recursive(root, 20);
    root = insertAvlTreeNode_recursive(root, 10);
    root = insertAvlTreeNode_recursive(root, 8);
    root = insertAvlTreeNode_recursive(root, 30);
    root = insertAvlTreeNode_recursive(root, 15);
    preOrderTraverseAvl(root);  // 20 10 8 15 30
    putchar(10);
    inOrderTraverseAvl(root);   // 8 10 15 20 30
    putchar(10);

    root = deleteNodeOfAvlTree_revursive(root, 30);
    preOrderTraverseAvl(root);  // 10 8 20 15
    putchar(10);
    inOrderTraverseAvl(root);   // 8 10 15 20
    putchar(10);
}

void deleteAvlNodeRR()
{
    AvlTreeNode* root = NULL;
    root = insertAvlTreeNode_recursive(root, 20);
    root = insertAvlTreeNode_recursive(root, 10);
    root = insertAvlTreeNode_recursive(root, 30);
    root = insertAvlTreeNode_recursive(root, 25);
    root = insertAvlTreeNode_recursive(root, 40);
    preOrderTraverseAvl(root);  // 20 10 30 25 40
    putchar(10);
    inOrderTraverseAvl(root);   // 10 20 25 30 40
    putchar(10);

    root = deleteNodeOfAvlTree_revursive(root, 10);
    preOrderTraverseAvl(root);  // 30 20 25 40
    putchar(10);
    inOrderTraverseAvl(root);   // 20 25 30 40
    putchar(10);
}

void deleteAvlNodeRL()
{
    AvlTreeNode* root = NULL;
    root = insertAvlTreeNode_recursive(root, 20);
    root = insertAvlTreeNode_recursive(root, 10);
    root = insertAvlTreeNode_recursive(root, 30);
    root = insertAvlTreeNode_recursive(root, 25);
    preOrderTraverseAvl(root);  // 20 10 30 25
    putchar(10);
    inOrderTraverseAvl(root);   // 10 20 25 30
    putchar(10);

    root = deleteNodeOfAvlTree_revursive(root, 10);
    preOrderTraverseAvl(root);  // 25 20 30
    putchar(10);
    inOrderTraverseAvl(root);   // 20 25 30
    putchar(10);
}


/*
    1.root就是最小不平衡子树的根节点  2.注意是右子树不是右节点
    LL(右旋): 在root的左子树的根节点的 [左子树] 插入节点而破坏平衡.
    RR(左旋): 在root的右子树的根节点的 [右子树] 插入节点而破坏平衡.
    LR(左右旋): 在root的左子树的根节点的 [右子树] 插入节点而破坏平衡.
    RL(右左旋): 在root的右子树的根节点的 [左子树] 插入节点而破坏平衡.
       10                    20                     20                        20           10                       10                                  10                10           
          \      RR 左旋    /   \      LL 右旋      /  \    LR 左右旋         /   \        /  \                     /   \            RL 右左旋          /    \           /     \             
           20   ------->   10   30    -------->   8    30    --------->    10     30     8   20     --------->    8      30         -------->        8      30         8      40  
            \             /                      / \                      /             / \    \                 / \    /  \                       /  \    /  \       / \    /  \
             30          8                      6  10                    8             6   9    30              6   9  20   50                     6   9  20  40     6   9  30   50
                        /                          /                    / \                                                /  \                              /  \           / \   \
                       6                          9                    6   9                                              40   60                           35   50        20 35   60
                                                                                                                         /                                        \       
                                                                                                                        35                                        60        
*/
int main()
{
    AvlTreeNode* root = NULL;
    root = insertAvlTreeNode_recursive(root, 10);
    root = insertAvlTreeNode_recursive(root, 20);
    printf("root->left height:%d\n", avlTreeHeight(root->left));
    printf("root->right height:%d\n", avlTreeHeight(root->right));
    root = insertAvlTreeNode_recursive(root, 30);
    root = insertAvlTreeNode_recursive(root, 8);
    root = insertAvlTreeNode_recursive(root, 6);
    root = insertAvlTreeNode_recursive(root, 9);
    root = insertAvlTreeNode_recursive(root, 50);
    root = insertAvlTreeNode_recursive(root, 60);
    root = insertAvlTreeNode_recursive(root, 40);
    root = insertAvlTreeNode_recursive(root, 35);

    preOrderTraverseAvl(root);  // 10 8 6 9 40 30 20 35 50 60
    putchar(10);
    inOrderTraverseAvl(root);   // 6 8 9 10 20 30 35 40 50 60
    putchar(10);
    postOrderTraverseAvl(root); // 6 9 8 20 35 30 60 50 40 10
    putchar(10);

    root = deleteNodeOfAvlTree_revursive(root, 20);
    root = deleteNodeOfAvlTree_revursive(root, 35);
    root = deleteNodeOfAvlTree_revursive(root, 30);

    preOrderTraverseAvl(root);  // 10 8 6 9 50 40 60
    putchar(10);
    inOrderTraverseAvl(root);   // 6 8 9 10 40 50 60
    putchar(10);

    // deleteAvlNodeLL();
    // deleteAvlNodeLR();
    // deleteAvlNodeRR();
    deleteAvlNodeRL();
    
    return 0;
}

