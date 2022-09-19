#include <iostream>

using namespace std;
typedef struct _Node
{
    int data;
    struct _Node *next;
}Node;


class singlelist
{
public:
    singlelist():m_headnode(NULL)
    {
        cout << "singlelist()" << endl;
    }
    ~singlelist()
    {
        cout << "~singlelist()" << endl;
    }
    void createlist();
    void destroylist();
    void insertnode(int n);
    void deletenode(int n);
    Node* searchnode(int n);
    void traverselist();
    void reverselist();
    int listlen();
private:
    Node *m_headnode;
};
void singlelist::createlist()
{
    m_headnode = new Node;
    m_headnode->next = nullptr;
}
void singlelist::insertnode(int n)
{
    Node* newnode = new Node;
    if(newnode)
    {
        newnode->data = n;
        newnode->next = m_headnode->next;
        m_headnode->next = newnode;
    }
}
void singlelist::traverselist()
{
    if(m_headnode)
    {
        Node* p = m_headnode->next;
        while (p != nullptr) {
            cout << "p addr: " << p << ",data: " << p->data <<endl;
            p = p->next;
        }
    }
}
int singlelist::listlen()
{
    int len = 0;
    if(m_headnode)
    {
        Node* p = m_headnode->next;
        while (p != nullptr) {
            len++;
            p = p->next;
        }
    }
    return len;
}
void singlelist::destroylist()
{
    if(m_headnode == nullptr)
    {
        return;
    }
    Node *p = m_headnode;
    while (p) {
        m_headnode = m_headnode->next;
        delete p;
        p = NULL;
        p = m_headnode;
    }
}
Node* singlelist::searchnode(int n)
{
    if(m_headnode)
    {
        Node * ptmp = m_headnode->next;
        while (ptmp) {
            if(ptmp->data == n)
            {
                return ptmp;
            }
            ptmp = ptmp->next;
        }

    }
    return nullptr;
}
void singlelist::deletenode(int n)
{
    if(m_headnode == nullptr)
    {
        cout << "deletenode fail m_headnode is null" << endl;
        return;
    }
    Node *p = m_headnode;
    while (p->next) {
        if(p->next->data == n)
        {
            break;
        }
        p= p->next;
    }
    if(p)
    {
        Node *ptmp = p->next;
        p->next = ptmp->next;
        delete ptmp;
        ptmp = nullptr;
        cout << "delete node success" << endl;
    }
}
void singlelist::reverselist()
{
    if(m_headnode == nullptr)
    {
        return;
    }
    Node *p = m_headnode->next;
    Node *ptmp = p;
    m_headnode->next = nullptr;
    while (p) {
        ptmp = ptmp->next;
        p->next = m_headnode->next;
        m_headnode->next = p;
        p = ptmp;
    }

}
int main()
{
    singlelist sl;
    sl.createlist();
    sl.insertnode(1);
    sl.insertnode(2);
    sl.insertnode(3);
    sl.insertnode(4);
    sl.insertnode(5);

    int len = sl.listlen();
    cout << "len:" << len << endl;
    sl.traverselist();
//    Node*p = sl.searchnode(5);
//    if(p)
//    {
//        cout << "p: " << p << "data:"<< p->data <<endl;
//    }

//    sl.deletenode(1);
//    sl.deletenode(5);
//    cout <<"len:" << sl.listlen() << endl;
    cout << "-------------------" << endl;

    sl.reverselist();
    sl.traverselist();

    sl.destroylist();
    len = sl.listlen();
    cout << "len:" << len << endl;

    return 0;
}








