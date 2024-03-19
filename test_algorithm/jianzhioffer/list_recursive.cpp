#include <algorithm>
#include <cstdint>
#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* next;
};

//求链表中的最大整数。(递归)
int findMax_recursive(Node* head)
{
    if (head == nullptr) {
        return INT32_MIN;
    }

    int maxValue = findMax_recursive(head->next);
    return std::max(maxValue, head->data);
}

//求链表节点的个数（递归）
int countNodes_recursive(Node* head)
{
    if (head == nullptr) {
        return 0;
    }

    return 1 + countNodes_recursive(head->next);
}

//计算所有整数的平均值（递归）
double calAverage_recusive(Node* head, int sum, int count)
{
    if (head == nullptr) {
        return (double)sum / count;
    }

    return calAverage_recusive(head->next, sum + head->data, count + 1);
}

void print_list(Node* head)
{
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main()
{
    Node node1 = {1, nullptr};
    Node node2 = {2, nullptr};
    Node node3 = {3, nullptr};
    Node node4 = {4, nullptr};
    Node node5 = {5, nullptr};
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    print_list(&node1);

    int maxV = findMax_recursive(&node1);
    cout << "maxV: " << maxV << endl;

    int node_count = countNodes_recursive(&node1);
    cout << "node_count: " << node_count << endl;

    int average = calAverage_recusive(&node1, 0, 0);
    cout << "average: " << average << endl;

    return 0;
}