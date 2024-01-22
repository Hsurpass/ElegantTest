#include <iostream>
#include <unordered_set>

using namespace std;

struct ListNode {
    int data;
    struct ListNode* next;

    ListNode(int d):data(d), next(NULL) {}
};

// 无序链表去重使用hash表
ListNode* removeDuplicateNode(ListNode* head)
{
    if(head == NULL || head->next == NULL)
        return head;
    
    ListNode* prev = head, *cur = head->next;
    // 使用hash表，时间复杂度为O(N)，空间复杂度为O(1)
    // unordered_set<int> hashset;
    // hashset.insert(prev->data);
    int hashset[10000] = {0};

    while (cur)
    {
        // if(hashset.find(cur->data) != hashset.end())
        if(hashset[cur->data] == 1)
        {
            prev->next = cur->next;
            delete cur;
            cur = prev->next;
        }
        else
        {
            // hashset.insert(cur->data);
            hashset[cur->data] = 1;
            prev = cur;
            cur = cur->next;
        }
    }
    
    return head;
}

void test_removeDuplicateNode()
{
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(2);
    head->next->next->next->next = new ListNode(3);
    head->next->next->next->next->next = new ListNode(4);

    ListNode* node = removeDuplicateNode(head);
    ListNode* tmp = node;
    while(node)
    {
        cout << node->data << " ";
        node = node->next;
    }
    putchar(10);

    while (tmp)
    {
        ListNode* t = tmp;
        tmp = t->next;
        delete t;
    }
    
}


/************************************************/
// 有序链表去重使用双指针遍历，不需要hash表
ListNode* orderedListRemoveDuplicateNode(ListNode* head)
{  
    if(head == NULL || head->next == NULL)
        return head;
    
    ListNode* prev = head, *cur = head->next;

    while (cur)
    {
        if(prev->data == cur->data)
        {
            prev->next = cur->next;
            delete cur;
            cur = prev->next;
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
    
    return head;
}

void test_orderedListRemoveDuplicateNode()
{
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(3);
    head->next->next->next->next = new ListNode(4);
    head->next->next->next->next->next = new ListNode(4);

    ListNode* node = orderedListRemoveDuplicateNode(head);
    ListNode* tmp = node;
    while(node)
    {
        cout << node->data << " ";
        node = node->next;
    }
    putchar(10);

    while (tmp)
    {
        ListNode* t = tmp;
        tmp = t->next;
        delete t;
    }
    
}

int main()
{
    // test_removeDuplicateNode();
    test_orderedListRemoveDuplicateNode();

    return 0;
}