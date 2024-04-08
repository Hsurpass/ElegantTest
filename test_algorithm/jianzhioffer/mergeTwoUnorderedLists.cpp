#include <climits>
#include <iostream>

using namespace std;

struct LinkList
{
    int data;
    struct LinkList* next;
};

LinkList* find_greater_node(LinkList* list, LinkList* node)
{
    LinkList* prev = nullptr;
    while (list && node->data > list->data) {
        prev = list;
        list = list->next;
    }
    return prev;
}

LinkList* merge_two_unorder_list(LinkList* l1, LinkList* l2)
{
    LinkList node = {INT_MIN, nullptr};
    LinkList* tmp = &node;

    // node -> 1 -> 3 -> 5 -> NULL
    LinkList* l1next = nullptr;
    while (l1) {
        l1next = l1->next;
        tmp = find_greater_node(tmp, l1);
        l1->next = tmp->next;
        tmp->next = l1;

        l1 = l1next;
        tmp = &node;
    }

    LinkList* l2next = nullptr;
    while (l2) {
        l2next = l2->next;
        tmp = find_greater_node(tmp, l2);
        l2->next = tmp->next;
        tmp->next = l2;

        l2 = l2next;
        tmp = &node;
    }

    return tmp->next;
}

void test_mergeTwoOrderedLists_iterator()
{
    LinkList node1{5, nullptr};
    LinkList node2{1, nullptr};
    LinkList node3{3, nullptr};

    LinkList node4{2, nullptr};
    LinkList node5{8, nullptr};
    LinkList node6{6, nullptr};
    LinkList node7{4, nullptr};

    node1.next = &node2;
    node2.next = &node3;

    node4.next = &node5;
    node5.next = &node6;
    node6.next = &node7;

    LinkList* tmp = merge_two_unorder_list(&node1, &node4);

    while (tmp) {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
    putchar(10);
}

int main()
{
    test_mergeTwoOrderedLists_iterator();

    return 0;
}