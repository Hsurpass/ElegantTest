#include <iostream>
#include <stack>

using namespace std;

class Node
{
public:
    Node(int i) : data(i), next(nullptr)
    {}
    int data;
    Node* next;
};

/*
->->->->-\
          ->->->->
->->->->-/
*/

bool is_cross(Node* l1, Node* l2)
{
    if (!l1 || !l2)
        return false;

    while (l1) {
        l1 = l1->next;
    }

    while (l2) {
        l2 = l2->next;
    }

    return l1 == l2;
}

// 不使用栈
// 先计算两个链表的长度，再减去多余的长度，开始遍历。
Node* find_list_cross_point(Node* l1, Node* l2)
{
    if (!l1 || !l2) {
        return nullptr;
    }

    Node* p1 = l1;
    Node* p2 = l2;
    int len1 = 0;
    int len2 = 0;

    while (p1) {
        len1++;
        p1 = p1->next;
    }

    while (p2) {
        len2++;
        p2 = p2->next;
    }

    p1 = l1;
    p2 = l2;
    int step = len1 - len2;
    if (step > 0) {
        for (int i = 0; i < step; i++) {
            p1 = p1->next;
        }
    }
    else {
        for (int i = 0; i < step; i++) {
            p2 = p2->next;
        }
    }

    while (p1 && p2) {
        if (p1 == p2) {
            break;
        }

        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;
}

// 使用栈
Node* find_list_cross_point_by_stack(Node* l1, Node* l2)
{
    std::stack<Node*> sn1, sn2;

    while (l1) {
        sn1.push(l1);
        l1 = l1->next;
    }

    while (l2) {
        sn2.push(l2);
        l2 = l2->next;
    }

    Node* prev = nullptr;
    while (!sn1.empty() && !sn2.empty()) {

        if (sn1.top() == sn2.top()) {
            prev = sn1.top();
            sn1.pop();
            sn2.pop();
        }
        else {
            return prev;
        }
    }
    return prev;
}

void test_list_cross()
{
    Node node1(1), node2(2), node3(3), node4(4), node5(5);
    Node node6(6), node7(7);

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;

    node6.next = &node4;
    node7.next = &node5;

    bool isCross = is_cross(&node1, &node6);
    cout << isCross << endl;

    // Node* node = find_list_cross_point(&node1, &node6);
    Node* node = find_list_cross_point_by_stack(&node1, &node6);
    cout << node->data << endl;
}

int main()
{
    test_list_cross();

    return 0;
}