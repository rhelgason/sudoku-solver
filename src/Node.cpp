#include "Node.h"

Node::Node() {
    left = right = up = down = colHead = this;
    cand = -1;
}

Node::Node(Node* l, Node *r) {
    left = l;
    right = r;
    up = down = colHead = this;
    cand = 0;
}

void Node::setRight(Node * n) {
    right = n;
}

void Node::setLeft(Node * n) {
    left = n;
}

void Node::setUp(Node * n) {
    up = n;
}

void Node::setDown(Node * n) {
    down = n;
}

Node* Node::getRight() {
    return right;
}

Node* Node::getLeft() {
    return left;
}

Node* Node::getUp() {
    return up;
}

Node* Node::getDown() {
    return down;
}