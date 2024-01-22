#include <iostream>
#include <string>

using namespace std;

struct ListNode
{
    int val;
    struct ListNode* next;
    ListNode(int x) : val(x), next(nullptr)
    {}
};

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param head ListNode类 
     * @param n int整型 
     * @return ListNode类
     */
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        if (head == NULL) {
            return head;
        }

        int count = 0;
        ListNode* cur = head;
        while (cur) {
            ++count;
            cur = cur->next;
        }

        int m = count - n;
        int i = 1;
        cur = head;
        while (i < m) {
            cur = cur->next;
            i++;
        }
        cout << m << cur->val << endl;

        ListNode* deleteNode = NULL;
        if (m == 0) {
            deleteNode = cur;
            head = deleteNode->next;
        }
        else {
            deleteNode = cur->next;
            cur->next = deleteNode->next;
        }

        delete deleteNode;

        return head;
    }
};

int main()
{
    ListNode* node1 = new ListNode(1);
    node1->next = new ListNode(2);
    node1->next->next = new ListNode(3);
    node1->next->next->next = new ListNode(4);
    node1->next->next->next->next = new ListNode(5);

    Solution s;
    ListNode* head = s.removeNthFromEnd(node1, 2);

    ListNode* node = head;
    while (node) {
        cout << node->val << " ";
        node = node->next;
    }
    cout << endl;

    ListNode* t = NULL;
    while (head) {
        t = head;
        head = t->next;
        delete t;
    }
}
