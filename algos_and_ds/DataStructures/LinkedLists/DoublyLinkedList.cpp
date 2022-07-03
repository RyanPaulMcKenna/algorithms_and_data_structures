
#include <iostream>

using namespace std;

// Doubly Linked-List
class Node {
    public:
        float data;
        Node* next;
        Node* prev;

};

void insert(Node* &b, float a)
{
    if (b == nullptr)
    {    
        b = new Node();
        b->data = a;
        b->next = nullptr;
        b->prev = nullptr;
    } else {
        
        // Inserts at front.
        Node* C = new Node();
        C->next = b;
        C->data = a;
        C->prev = nullptr;
        b->prev = C;
        b = C;
    }
};

Node* ListSearch(Node* L, float k) // Worst case: O(n)
{
    Node* x = L;
    while(x != nullptr && x->data != k)
        x = x->next;
    return x;
}

void ListDelete(Node* L, Node* x) // Runs in O(1) but if Search must be called first then runs in O(n).
{
    if (x->prev != nullptr)
        x->prev->next = x->next;
    else
        L = x->next;
    
    if (x->next != nullptr)
        x->next->prev = x->prev;
}


int main()
{
    Node* L = nullptr;
    insert(L,0.1);
    cout << L->data << endl;
    insert(L,0.2);
    cout << L->data << " " << L->next->data << endl;
    cout << L->next->prev->data;
    int x;
    cin >> x;
}