#include <iostream>

/*  If H(x) == H(y) then x and y mite be equal.
    but if H(x) != H(y) then x andy are definitely not equal.

    So instead of comparing x and y 
    compare H(x) and H(y) because it takes only O(1).

    A hash function must be deterministic. H(x) = a , H(y) = b, but H(y) != a.

    Hash functions should be uniform to reduce likelyhood of collisions.

    keys x must be immutable. H(x).

    Lookup, insertion and removal. O(1).

    If using separate chaining and array of linked lists get full and linked lists get long then
    you need to make a new bigger table and rehash your data into the larger table,
    shortening the linked-lists.

    Load Factor = number of items in the table / the size of the table.

    Example hash function:
    int hashFunc(int x) // Maps a key to a whole number in a fixed range.
    {
        return (x^2 - 6*x + 9) % 10; // range: [0 9]
    }
*/
const int DefaultTableSize = 5;
// ---------------------------------------------------------------------------------//
template<class K, class V>
class Entry
{
    public:
    
    K key;
    V value;
    int hash;
    
    Entry<K,V>() {}

    Entry<K,V>(K key, V value)
    {
        this->key = key;
        this->value = value;
    }

    friend bool operator==(const Entry<K,V> &l, const Entry<K,V> &r)
    {
        if (l.hash != r.hash)
            return false;
        return l.key == r.key;
    }
    friend bool operator!=(const Entry<K,V> &l, const Entry<K,V> &r)
    {
        if (l.hash != r.hash)
            return true;
        return l.key != r.key;
    }
};

template<class K, class V>
std::ostream& operator<<(std::ostream& os, const Entry<K,V> &obj)
{
    os << "(" << obj.key << " => " << obj.value << ")";
    return os;
};

// Doubly Linked-List for seperate chaining.
template<class K, class V>
class Node {
    public:
        Entry<K,V> data;
        Node<K,V>* next;
        Node<K,V>* prev;

};

template<class K, class V>
void insert(Node<K,V>* &b, Entry<K,V> a)
{
    if (b == nullptr)
    {    
        b = new Node<K,V>();
        b->data = a;
        b->next = nullptr;
        b->prev = nullptr;
    } else {
        
        // Inserts at back.
        Node<K,V>* tmp1 = b;
        Node<K,V>* prev;
        while (tmp1 != nullptr)
        {
            prev = tmp1;
            tmp1 = prev->next;
        }

        Node<K,V>* &i = prev->next;
        i = new Node<K,V>();
        i->data = a;
        i->next = nullptr;
        i->prev = prev;
    }
};

template<class K, class V>
Node<K,V>* ListSearch(Node<K,V>* L, Entry<K,V> M) // Worst case: O(n)
{
    Node<K,V>* x = L;
    while(x != nullptr && x->data.key != M.key)
        x = x->next;
    return x;
}

template<class K, class V>
Node<K,V>* ListDelete(Node<K,V>* &L, Node<K,V>* x) // Worst case: O(n)
{
    if (x->prev != nullptr)
        x->prev->next = x->next;
    else
        L = x->next;
    
    if (x->next != nullptr)
        x->next->prev = x->prev;
    
    return x;
}


class HtSeperateChaining
{
    private:
    int tableSize;
    int itemsInTable;
    int loadFactor;
    Node<std::string,int>* T[DefaultTableSize];

    public:
    HtSeperateChaining()
    {
        tableSize = DefaultTableSize;
        itemsInTable = 0;
        loadFactor = itemsInTable / tableSize;
        for (int i = 0; i < tableSize; i++)
            T[i] = nullptr;
    }

    int HashFunction(const Entry<std::string,int> entry)
    {
        return (entry.key.length() + entry.value) % tableSize; // puts values in range 0,1,2,3,4,5
    }

    void Insert(Entry<std::string, int> entry)
    {
        int hash = HashFunction(entry);
        entry.hash = hash;
        insert<std::string,int>(T[hash],entry); // linked-list handles insert, hash func just chooses where.
        itemsInTable++;
        loadFactor = itemsInTable / tableSize;
    }

    Node<std::string,int>* Delete(Node<std::string,int>*  x)
    {
        --itemsInTable;
        loadFactor = itemsInTable / tableSize;
        int hash = HashFunction(x->data);
        return ListDelete<std::string,int>(T[hash], x);
    }

    Node<std::string,int>* search(Entry<std::string, int> x)
    {
        int hash = HashFunction(x);
        return ListSearch<std::string,int>(T[hash], x);
    }

    void printTable()
    {
        for (int i = 0; i < tableSize; i++)
        {
            std::cout << "T[" << (i+1) << "] ";
            if (T[i] != nullptr)
            {
                Node<std::string,int>* tmp = T[i];
                while(tmp != nullptr)
                {
                    std::cout << " -> " << tmp->data;
                    tmp = tmp->next;
                }
                std::cout << "\n";
            } else {
                std::cout << "NIL\n";
            }
        }
    }

};

int main()
{
    // Hash Table.

    // Separate Chaining -> mainting a datastructure such as a linked-list.
    // Node<std::string,int>* table[5];
    Entry<std::string, int> p1,p2,p3,p4,p5,p6,p7,p8,p9,p10;
    p1.key = "Rai";  p1.value = 25;
    p2.key = "Rick"; p2.value = 61;
    p3.key = "Will"; p3.value = 21;
    p4.key = "Leah"; p4.value = 18;
    p5.key = "Lara"; p5.value = 34;
    p6.key = "Ryan"; p6.value = 56;
    p7.key = "Finn"; p7.value = 21;
    p8.key = "Mark"; p8.value = 10;
    p9.key = "Felix"; p9.value = 101;
    p10.key = "Anita"; p10.value = 17;

    HtSeperateChaining myTbl;
    myTbl.Insert(p1);
    myTbl.Insert(p2);
    myTbl.Insert(p3);
    myTbl.Insert(p4);
    myTbl.Insert(p5);
    myTbl.Insert(p6);
    myTbl.Insert(p7);
    myTbl.Insert(p8);
    myTbl.Insert(p9);
    myTbl.Insert(p10);
    
    myTbl.printTable();

    Node<std::string, int>* node = myTbl.search(p9);
    std::cout << "\nFound " << node->data.key << " at position T[" << node->data.hash + 1 << "]\n";
    std::cout << "\nDELETE: Felix\n\n"; 
    myTbl.Delete(node);

    myTbl.printTable();


    //------------------------------------------//
    int x;
    std::cin >> x;
}