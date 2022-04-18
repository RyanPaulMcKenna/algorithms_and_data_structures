#include <iostream>

/*
 Red-black tree properies:
 1) Every node is either red or black.
 2) The root is black.
 3) Every leaf(NIL) is black.
 4) If a node is red, then both its children are black.
 5) For each node, all paths from the node to descendant leaves contain the same number of black nodes.


 Black-height of a node x, hb(x) = number of black nodes from but not including x to a leaf via any simple path.
 
 When inserting or deleting the colors must be reset to maintain the properties of the red-black tree.
 In addition the node must be ROTATED. Rotations are achieved by changing the pointer structure via rotation.

*/

class Node {
    public:
        bool color; // 1 for black 0 for red.
        Node* parent; // root must be nullptr which counts as black.
        Node* left;
        Node* right;
        int key;
};
Node SENTINEL;
Node* NIL = &SENTINEL;

void rightRotate(Node* T, Node* x) // Run in O(1) time.
{
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NIL)
        y->right->parent = x;
    y->parent = x->parent;

    if (x->parent == NIL)
        T = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    
    y->right = x;
    x->parent = y;
};

void leftRotate(Node* T, Node* x) // Run in O(1) time.
{
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL)
        y->left->parent = x;
    y->parent = x->parent;

    if (x->parent == NIL)
        T = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
};

void RedBlackInsertFixup(Node* T, Node* z)
{
    Node* y;
    while (z->parent->color == false) // Red.
    {
        // P[z] is left child of its parent.
        if (z->parent == z->parent->parent->left) 
        {
            y = z->parent->parent->right; // Uncle.
            if (y->color == false) // Red uncle.
            {
                // Case 1.
                z->parent->color = true;
                y->color = true;
                z->parent->parent->color = false;
                z = z->parent->parent;
                continue; // skip to next iteration.
            } else if (z == z->parent->right) // Black Uncle.
            {
                // Case 2.
                z = z->parent;
                leftRotate(T,z);
            }
            // Case 3.
            z->parent->color = true;
            z->parent->parent->color = false;
            rightRotate(T,z);
        } else {
            // P[z] is right child of its parent.

            y = z->parent->parent->left; // Uncle.
            if (y->color == false) // Red uncle.
            {
                // Case 1.
                z->parent->color = true;
                y->color = true;
                z->parent->parent->color = false;
                z = z->parent->parent;
                continue; // skip to next iteration.
            } else if (z == z->parent->left) // Black Uncle.
            {
                // Case 2.
                z = z->parent;
                rightRotate(T,z);
            }
            // Case 3.
            z->parent->color = true;
            z->parent->parent->color = false;
            leftRotate(T,z);
        }
    }
    T->color = true;

};

void RedBlackInsert(Node* T, Node* z)
{
    Node* y = NIL;
    Node* x = T;

    while(x != NIL)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NIL)
        T = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    z->left = NIL;   // Black.
    z->right = NIL; // Black.
    z->color = false; // RED.
    RedBlackInsertFixup(T,z);
};

void InorderTreeWalk(Node* x)
{
    if (x != NIL)
    {
        InorderTreeWalk(x->left); 
        std::cout << x->key << " ";
        InorderTreeWalk(x->right);
    }
};

Node* TreeMinimum(Node* x)
{
    Node* it= x;
    while(it->left != NIL)
        it = it->left;
    return it;
}

Node* TreeMaximum(Node* x)
{
    Node* it = x;
    while(it->right != NIL)
        it = it->right;
    return it;
}

Node* TreeSuccesor(Node* x)
{
    if (x->right != NIL)
        return TreeMinimum(x->right);
    Node* y = x->parent;
    Node* tmp = x;
    while (y != NIL && tmp == y->right)
    {
        tmp = y;
        y = y->parent;
    }
    return y;
}

void RedBlackDeleteFixup(Node* T, Node* x) // NOT COMPLETE.
{
    Node* w;
    while(x != T && x->color == true)
    {
        if (x == x->parent->left)
        {
            w = x->parent->right;
            if (w->color == true) 
            {
                x->parent->color = false;
                leftRotate(T,x->parent);
                w = x->parent->right;
            }
            if (w->left->color == true && w->right->color == true)
            {
                w->color = false;
                x = x->parent;
            } else if (w->right->color == true) {
                w->left->color = true;
                w->color = false;
                rightRotate(T,w);
                w = x->parent->right;
            }
            // ???
            w->color = x->parent->color;
            x->parent->color = true;
            w->right->color = true;
            leftRotate(T,x->parent);
            x = T;
        } else {
            // left and right exchanged.
        }
    }
    x->color = true;
}

Node* RedBlackDelete(Node* T, Node* z)
{
    Node* y;
    Node* x;

    if (z->left == NIL || z->right == NIL)
        y = z; //  z has at most 1 child.
    else
        y = TreeSuccesor(z); // z has 2 children.

    if (y->left != NIL)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;
    if (y->parent == NIL)
        T = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;


    if (y != z)
        z->key = y->key;

    if (y->color == true)
        RedBlackDeleteFixup(T,x);

    return y;
}

int main()
{
    NIL->color = true; // Black. IMPORTANT.
    // NIL->left = NIL;
    // NIL->right = NIL;

    Node T;
    Node* root = &T;
    root->key = 10;
    root->color = true;
    root->parent = NIL;
    root->left = NIL;
    root->right = NIL;

    Node z;
    Node* Z = &z;
    Z->key = 5;
    Z->parent = nullptr;
    Z->left = NIL;
    Z->right = NIL;

    RedBlackInsert(root,Z);

    InorderTreeWalk(root);

    int x;
    std::cin >> x;
}