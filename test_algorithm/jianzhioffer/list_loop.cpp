#include <iostream>
#include <unordered_map>

using namespace std;

/*
1.确定链表存在环：
使用快慢指针法：
分别定义 fast 和 slow 指针，从头结点出发，fast 指针每次移动两个节点，slow 指针每次移动一个节点，如果 fast 和 slow 指针在途中相遇 ，说明这个链表有环。
fast指针一定先进入环中，如果 fast 指针和 slow 指针相遇的话，一定是在环中相遇。fast指针会先被困在环中，一直等待slow指针进入并相遇。

2. 确定存在环后，找到环的入口：
假设从头结点到环形入口节点 的节点数为 x 。 环形入口节点到 fast 指针与slow 指针相遇节点 节点数为 y 。 从相遇节点到环形入口节点节点数为 z 。
                    4为相遇点
                  |<- y->|  |<- z ->|
    1  ->  2  ->  3  ->  4  ->  5
                  ^_____________|
    |<- x  ->|   

slow 和 fast 指针相遇点处： slow 指针走过的节点数为: x + y， fast指针走过的节点数：x + y + n*(y + z)，
其中 n 为 fast 指针在环内走了 n 圈才遇到 slow 指针， （y+z）为 一圈内节点的个数。由于 slow 指针步幅为1，fast 指针步幅为 2，易得公式：
    2*(x+y) = x+y+n*(y+z)
    x+y = n*(y+z)
    x = n*(y+z)-y
    x = (n-1)*(y+z) + y + z -y
    x = (n-1)*(y+z) + z
得到 x = (n-1)*(y+z) + z ，其中 y+z 是环的长度，所以由此公式可得出结论：从相遇点到入环点的距离加上 n-1 圈的环长，恰好等于从链表头部到入环点的距离。
也就是从相遇点和头节点走过相同的步长，直道相遇时就是环的起始点。
于是，使用另一个指针指向头节点，步幅为1，与slow指针同步走，两个指针下次相遇的结点即为链表环的入口结点。
*/

class Node
{
public:
    Node(int i) : data(i), next(nullptr)
    {
        visit = false;
    }
    int data;
    Node* next;
    bool visit;
};

// bool is_loop_list(Node* l1)
Node* is_loop_list(Node* l1)
{
    Node* slow = l1;
    Node* fast = l1;

    while (slow && fast) {
        if (fast->next && fast->next->next) {
            fast = fast->next->next;
        }
        else {
            break;
        }

        slow = slow->next;

        if (slow == fast) {
            return slow;
            // return true;
        }
    }

    // return false;
    return nullptr;
}

Node* find_loop_first_node(Node* l1)
{
    Node* encounter_point = is_loop_list(l1);
    if (encounter_point) {
        Node* slow = l1;

        while (slow != encounter_point) {
            slow = slow->next;
            encounter_point = encounter_point->next;
        }

        return slow;
    }

    return nullptr;
}

Node* find_loop_list_first_node(Node* l1)
{
    Node* pre = l1;
    Node* curr = l1->next;
    unordered_multimap<Node*, Node*> topo_pre;

    while (!pre->visit) {
        topo_pre.emplace(curr, pre);
        pre->visit = true;

        pre = curr;
        curr = curr->next;
    }
    cout << "encounter point data: " << pre->data << endl;
    return pre; // 这里就已经能够求得起始点了

    cout << "element size: " << topo_pre.size() << endl;
    Node* first_node = nullptr;
    for (auto& itr : topo_pre) {
        int count = topo_pre.count(itr.first);
        cout << count << " ";
        if (count > 1) {
            first_node = itr.first;
        }
    }
    cout << endl;
    cout << "first_node data: " << first_node->data << endl;

    return first_node;
}

void test_loop_list()
{
    Node node1(1);
    Node node2(2);
    Node node3(3);
    Node node4(4);
    Node node5(5);

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = &node3;

    Node* node = is_loop_list(&node1);
    if (node) {
        cout << "list is loop" << endl;
    }
    else {
        cout << "list no loop" << endl;
    }

    node = find_loop_first_node(&node1);
    if (node) {
        cout << node->data << endl;
    }
    else {
        cout << "no loop list" << endl;
    }

    node = find_loop_list_first_node(&node1);
    if (node) {
        cout << node->data << endl;
    }
    else {
        cout << "no loop list" << endl;
    }
}

int main()
{
    test_loop_list();
    return 0;
}