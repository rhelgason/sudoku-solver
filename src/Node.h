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
        int row = -1;
    
    public:
        // basic constructor for matrix head
        Node();

        // constructor for column headers
        Node(Node* l, Node *r);

        // constructor for matrix entry
        Node(Node* l, Node* r, Node* u, Node* d, Node* c, int row);

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
        Node* getColHead();

        // candidate count functions
        void addCand();
        void removeCand();
        int getCand();

        // get the matrix column
        int getRow();

        // cover and uncover functions for column headers
        void cover();
        void uncover();
};

#endif