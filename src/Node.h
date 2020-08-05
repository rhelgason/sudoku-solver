#ifndef NODE_H
#define NODE_H

using namespace std;

// class representing an entry in the dancing links matrix
class Node {
    private:
        struct Node* left;
        struct Node* right;
        struct Node* up;
        struct Node* down;
        struct Node* colHead;
        int cand = -1;
    
    public:
        // basic constructor for matrix head
        Node();

        // constructor for column headers
        Node(Node* l, Node *r);

        // setters for each pointer
        void setRight(Node* n);
        void setLeft(Node* n);
        void setUp(Node* n);
        void setDown(Node* n);

        // getters for each pointer
        Node* getRight();
        Node* getLeft();
        Node* getUp();
        Node* getDown();
};

#endif