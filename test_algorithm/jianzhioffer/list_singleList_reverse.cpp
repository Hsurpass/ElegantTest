#include <iostream>
#include <stack>

using namespace std;

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL)
    {}
};

// 使用双指针来反转链表
ListNode* reverseList01(ListNode* head)
{
    ListNode* prev = NULL;
    ListNode* cur = head;

    while (cur) {
        ListNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    return prev;
}

// 使用头插法来反转链表
ListNode* reverseList02(ListNode* head)
{
    ListNode node(-1);
    ListNode* headNode = &node;

    while (head) {
        ListNode* next = head->next;

        head->next = headNode->next;
        headNode->next = head;

        head = next;
    }

    return headNode->next;
}

// 利用栈来反转链表
ListNode* reverseList03(ListNode* head)
{
    stack<ListNode*> s;
    while (head) {
        ListNode* next = head->next;
        s.push(head);
        head = next;
    }

    ListNode* h = s.top();
    s.pop();
    ListNode* tail = h;
    while (!s.empty()) {
        ListNode* currNode = s.top();
        s.pop();

        tail->next = currNode;
        tail = currNode;
    }
    tail->next = NULL;

    return h;
}

// 使用递归来翻转链表
/*
    head head->next
 1 -> 2 -> 3 -> NULL
head head->next 
*/
ListNode* reverseList_by_recursive(ListNode* head)
{
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* new_head = reverseList_by_recursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    return new_head;
}

int main()
{
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    // ListNode* reversedHead = reverseList01(head);
    // ListNode* reversedHead = reverseList02(head);
    // ListNode* reversedHead = reverseList03(head);
    ListNode* reversedHead = reverseList_by_recursive(head);

    ListNode* t = reversedHead;

    while (reversedHead != NULL) {
        cout << reversedHead->val << " ";
        reversedHead = reversedHead->next;
    }
    cout << endl;

    while (t) {
        ListNode* tmp = t->next;
        delete t;
        t = tmp;
    }

    return 0;
}