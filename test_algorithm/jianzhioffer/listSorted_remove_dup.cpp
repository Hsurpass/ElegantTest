// 一个有序的链表，去除重复的节点，要求空间复杂度为O1。例:1->2->2->4，去除后变成1->4

struct Node {
    int val;
    Node* next;
    Node(int v): val(v),next(nullptr) {}
};

Node* delDupNode(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }

    Node pre_head(0);
    pre_head.next = head;
    Node* prev = &pre_head;
    Node* curr = head;
    while (curr) {
        if (curr->next && curr->val == curr->next->val) {
            int dup_val = curr->val;
            while (curr && curr->val == dup_val) {
                Node* tmp = curr;
                curr = curr->next;
                delete tmp;
            }
            prev->next = curr;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    return pre_head.next;
}