#include <iostream>


// All operations run in Expected time O(h) ,h tree height of randomly built tree.

class Node {
    public:
        Node* parent;
        Node* left;
        Node* right;
        int key;
};

void InorderTreeWalk(Node* x)
{
    if (x != nullptr)
    {
        InorderTreeWalk(x->left); 
        std::cout << x->key << " ";
        InorderTreeWalk(x->right);
    }
}

Node* TreeSearch(Node* x, int k)
{
    if (x == nullptr || k == x->key)
        return x;
    if (k < x->key)
        TreeSearch(x->left,k);
    else
        TreeSearch(x->right,k);

    return x; // this should never happen.
}

Node* TreeSearchIterative(Node* x, int k)
{
    Node* it = x;
    while(it != nullptr && k != it->key)
        if (k < it->key)
            it = it->left;
        else
            it = it->right;
    return it;
}

Node* TreeMinimum(Node* x)
{
    Node* it= x;
    while(it->left != nullptr)
        it = it->left;
    return it;
}

Node* TreeMaximum(Node* x)
{
    Node* it = x;
    while(it->right != nullptr)
        it = it->right;
    return it;
}

Node* TreeSuccesor(Node* x)
{
    if (x->right != nullptr)
        return TreeMinimum(x->right);
    Node* y = x->parent;
    Node* tmp = x;
    while (y != nullptr && tmp == y->right)
    {
        tmp = y;
        y = y->parent;
    }
    return y;
}


Node* TreePredocessor(Node* x) // rework to be like above.
{
    if (x->left != nullptr)
        return TreeMaximum(x->left);
    Node* y = x->parent;
    while (y != nullptr && x == y->left)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

void TreeInsert(Node* T, Node* z)
{
    Node* y = nullptr;
    Node* x = T;

    while(x != nullptr)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == nullptr)
        T = z; // Tree was empty.
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z; 
}

Node* TreeDelete(Node* T, Node* z)
{
    Node* y;
    Node* x;

    if (z->left == nullptr || z->right == nullptr)
        y = z; //  z has at most 1 child.
    else
        y = TreeSuccesor(z); // z has 2 children.

    if (y->left != nullptr)
        x = y->left;
    else
        x = y->right;

    if (x != nullptr)
        x->parent = y->parent;

    if (y->parent == nullptr)
        T = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;


    if (y != z)
        z->key = y->key;

    return y;
}

int main()
{


    Node n1;
    Node n2;
    n1.parent = nullptr;
    n1.left = nullptr;
    n1.right = nullptr;
    n1.key = 20;
    n2.key = 5;
    n2.left = nullptr;
    n2.right = nullptr;
    Node* T = &n1; // root
    Node* z = &n2;


    /*
             20
           /    \
          5      23
         / \    /  \
        3  12  21   24 
    */

    TreeInsert(T,z);
    
    InorderTreeWalk(T);
    // Node* query = TreeSearch(T,20);
    // std::cout << query->key;

    // query = TreeSuccesor(z);
    // std::cout << query->key;
    std::cout << "\n";
    TreeDelete(T,z); // Delete 5;

    std::cout << "\n";

    InorderTreeWalk(T);


   //TreeInsert(n1,n3);
   //TreeInsert(n1,n4);
   //TreeInsert(n1,n5);
   //TreeInsert(n1,n6);
   //TreeInsert(n1,n7);


    int x;
    std::cin >> x;
}