
#include <iostream>

using namespace std;

// Doubly Linked-List
class Node {
    public:
        int data;
        Node* next;
        Node* prev;

};

// Inserts in constant time O(1).
void insert(Node* &L, Node* x)
{
    x->next = L->next;
    L->next->prev = x;
    L->next = x;
    x->prev = L;
};

Node* ListSearch(Node* L, int k) // Worst case: O(n)
{
    Node* x = L->next;
    while(x != nullptr && x->data != k)
        x = x->next;
    return x;
}

void ListDelete(Node* L, Node* x) // Runs in O(1) but if Search must be called first then runs in O(n).
{
    x->prev->next = x->next;
    x-next->prev = x->prev;
}


int main()
{
    // Circular.
    Node* NIL = new Node();
    NIL->data -1;
    NIL->next = NIL->prev;
    NIL->prev = NIL->next;

    // NEEDS TO BE TESTED.
}