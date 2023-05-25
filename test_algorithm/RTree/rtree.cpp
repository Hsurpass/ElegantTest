#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 定义点结构体
struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};

// 定义矩形结构体
struct Rect {
    double x1, y1, x2, y2;
    Rect(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
    bool contains(Point* p) {
        return p->x >= x1 && p->x <= x2 && p->y >= y1 && p->y <= y2;
    }
    double area() {
        return (x2 - x1) * (y2 - y1);
    }
};

// 定义节点结构体
struct Node {
    Rect* rect;
    vector<Node*> children;
    vector<Point*> points;
    bool is_leaf;
    Node(Rect* rect, bool is_leaf) : rect(rect), is_leaf(is_leaf) {}
    ~Node() {
        delete rect;
        for (auto child : children) {
            delete child;
        }
        for (auto point : points) {
            delete point;
        }
    }
};

// 定义R树类
class RTree {
public:
    RTree(int max_children) : max_children(max_children), root(nullptr) {}
    ~RTree() {
        delete root;
    }
    void insert(Point* p) {
        if (root == nullptr) {
            root = new Node(new Rect(p->x, p->y, p->x, p->y), true);
            root->points.push_back(p);
            return;
        }
        Node* leaf = choose_leaf(root, p);
        leaf->points.push_back(p);
        if (leaf->points.size() <= max_children) {
            return;
        }
        Node* split_node = split_leaf(leaf);
        adjust_tree(leaf, split_node);
    }
    void remove(Point* p) {
        if (root == nullptr) {
            return;
        }
        Node* leaf = find_leaf(root, p);
        if (leaf == nullptr) {
            return;
        }
        auto it = find(leaf->points.begin(), leaf->points.end(), p);
        if (it == leaf->points.end()) {
            return;
        }
        leaf->points.erase(it);
        if (leaf == root) {
            if (leaf->points.empty()) {
                delete root;
                root = nullptr;
            }
            return;
        }
        if (leaf->points.size() >= ceil(max_children / 2.0)) {
            return;
        }
        Node* parent = find_parent(root, leaf);
        Node* neighbor = find_neighbor(parent, leaf);
        if (neighbor == nullptr) {
            neighbor = parent->children[1];
        }
        if (neighbor->points.size() + leaf->points.size() > max_children) {
            redistribute(leaf, neighbor);
        } else {
            merge(leaf, neighbor);
            adjust_tree(leaf, nullptr);
        }
    }
    vector<Point*> search(Rect* rect) {
        vector<Point*> result;
        search(root, rect, result);
        return result;
    }
private:
    int max_children;
    Node* root;
    Node* choose_leaf(Node* node, Point* p) {
        if (node->is_leaf) {
            return node;
        }
        double min_increase = INFINITY;
        Node* min_child = nullptr;
        for (auto child : node->children) {
            double increase = enlarged_area(child->rect, p) - child->rect->area();
            if (increase < min_increase) {
                min_increase = increase;
                min_child = child;
            } else if (increase == min_increase) {
                if (child->rect->area() < min_child->rect->area()) {
                    min_child = child;
                }
            }
        }
        return choose_leaf(min_child, p);
    }
    Node* split_leaf(Node* leaf) {
        vector<Node*> groups = split_points(leaf->points, max_children);
        Node* new_leaf = new Node(new Rect(groups[0]->rect->x1, groups[0]->rect->y1, groups[0]->rect->x2, groups[0]->rect->y2), true);
        new_leaf->points = groups[1]->points;
        leaf->points = groups[0]->points;
        if (leaf == root) {
            root = new Node(new Rect(0, 0, 0, 0), false);
            root->children.push_back(leaf);
        }
        Node* split_node = new Node(new Rect(0, 0, 0, 0), false);
        split_node->children.push_back(leaf);
        split_node->children.push_back(new_leaf);
        adjust_rect(split_node);
        insert_child(root, split_node);
        return split_node;
    }
    void adjust_tree(Node* node, Node* split_node) {
        if (node == root) {
            if (split_node != nullptr) {
                Node* new_root = new Node(new Rect(0, 0, 0, 0), false);
                new_root->children.push_back(node);
                new_root->children.push_back(split_node);
                adjust_rect(new_root);
                root = new_root;
            }
            adjust_rect(node);
            return;
        }
        adjust_rect(node);
        if (split_node != nullptr) {
            Node* parent = find_parent(root, node);
            insert_child(parent, split_node);
            if (parent->children.size() > max_children) {
                Node* new_split_node = split_node_internal(parent);
                adjust_tree(parent, new_split_node);
            }
        }
        Node* parent = find_parent(root, node);
        if (parent->children.size() < ceil(max_children / 2.0)) {
            return;
        }
        Node* new_split_node = split_node_internal(parent);
        adjust_tree(parent, new_split_node);
    }
    Node* find_leaf(Node* node, Point* p) {
        if (node->is_leaf) {
            return node;
        }
        for (auto child : node->children) {
            if (child->rect->contains(p)) {
                return find_leaf(child, p);
            }
        }
        return nullptr;
    }
    Node* find_parent(Node* node, Node* child) {
        if (node->is_leaf) {
            return nullptr;
        }
        for (auto c : node->children) {
            if (c == child) {
                return node;
            }
            Node* parent = find_parent(c, child);
            if (parent != nullptr) {
                return parent;
            }
        }
        return nullptr;
    }
    Node* find_neighbor(Node* parent, Node* node) {
        if (parent->children.size() == 1) {
            return nullptr;
        }
        for (int i = 0; i < parent->children.size(); i++) {
            if (parent->children[i] == node) {
                if (i == 0) {
                    return parent->children[i + 1];
                } else if (i == parent->children.size() - 1) {
                    return parent->children[i - 1];
                } else {
                    if (parent->children[i - 1]->points.size() > parent->children[i + 1]->points.size()) {
                        return parent->children[i - 1];
                    } else {
                        return parent->children[i + 1];
                    }
                }
            }
        }
        return nullptr;
    }
    void redistribute(Node* node1, Node* node2) {
        Node* parent = find_parent(root, node1);
        Rect* rect1 = node1->rect;
        Rect* rect2 = node2->rect;
        if (rect1->x1 < rect2->x1) {
            vector<Point*> points = node2->points;
            node2->points.clear();
            for (int i = points.size() - 1; i >= 0; i--) {
                if (node1->points.size() >= ceil(max_children / 2.0)) {
                    break;
                }
                node1->points.push_back(points[i]);
                points.erase(points.begin() + i);
            }
            reverse(points.begin(), points.end());
            node2->points = points;
            adjust_rect(node1);
            adjust_rect(node2);
            adjust_rect(parent);
        } else if (rect1->x1 > rect2->x1) {
            vector<Point*> points = node1->points;
            node1->points.clear();
            for (int i = points.size() - 1; i >= 0; i--) {
                if (node2->points.size() >= ceil(max_children / 2.0)) {
                    break;
                }
                node2->points.push_back(points[i]);
                points.erase(points.begin() + i);
            }
            reverse(points.begin(), points.end());
            node1->points = points;
            adjust_rect(node1);
            adjust_rect(node2);
            adjust_rect(parent);
        } else if (rect1->y1 < rect2->y1) {
            vector<Point*> points = node2->points;
            node2->points.clear();
            for (int i = points.size() - 1; i >= 0; i--) {
                if (node1->points.size() >= ceil(max_children / 2.0)) {
                    break;
                }
                node1->points.push_back(points[i]);
                points.erase(points.begin() + i);
            }
            reverse(points.begin(), points.end());
            node2->points = points;
            adjust_rect(node1);
            adjust_rect(node2);
            adjust_rect(parent);
        } else {
            vector<Point*> points = node1->points;
            node1->points.clear();
            for (int i = points.size() - 1; i >= 0; i--) {
                if (node2->points.size() >= ceil(max_children / 2.0)) {
                    break;
                }
                node2->points.push_back(points[i]);
                points.erase(points.begin() + i);
            }
            reverse(points.begin(), points.end());
            node1->points = points;
            adjust_rect(node1);
            adjust_rect(node2);
            adjust_rect(parent);
        }
    }
    void merge(Node* node1, Node* node2) {
        Node* parent = find_parent(root, node1);
        Rect* rect1 = node1->rect;
        Rect* rect2 = node2->rect;
        if (rect1->x1 < rect2->x1) {
            node1->points.insert(node1->points.end(), node2->points.begin(), node2->points.end());
            node1->children.insert(node1->children.end(), node2->children.begin(), node2->children.end());
            node2->points.clear();
            node2->children.clear();
            delete_child(parent, node2);
            adjust_rect(node1);
            adjust_rect(parent);
        } else if (rect1->x1 > rect2->x1) {
            node2->points.insert(node2->points.end(), node1->points.begin(), node1->points.end());
            node2->children.insert(node2->children.end(), node1->children.begin(), node1->children.end());
            node1->points.clear();
            node1->children.clear();
            delete_child(parent, node1);