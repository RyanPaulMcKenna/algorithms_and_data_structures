#include <iostream>
#include <math.h>       /* floor */

/*
OPEN ADDRESSING

LINEAR PROBING: P(x) = ax + b, with constants a,b

QUADRATIC PROBING: P(x) = ax^2 + bx + c, with constants a,b,c

DOUBLE HASHING: P(k,x) = x*H_2(k), where H_2(k) is a secondary hash function

PSEUDO RANDOM NUMBER GENERATOR: P(k,x) = x*RNG(H(k),x), where RNG is a random number generator seeded with H(k).

*/



template<class K, class V>
class Entry
{
    public:
    
    K key;
    V value;
    bool tombstone;
    int hash;
    
    Entry<K,V>() 
    {
        tombstone = false;
    }

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

const int DefaultTableSize = 12;
class HashTableLinearProbing
{
    private:
    int tableSize;
    int itemsInTable;
    int probingFactor;
    float maxLoadFactor;
    float loadFactor;
    Entry<std::string,int>** table;

    public:
    HashTableLinearProbing()
    {
        
        maxLoadFactor = 0.35;
        probingFactor = 5; // probing factor and DefaultTableSize are relatively prime.
        tableSize = DefaultTableSize;
        itemsInTable = 0;
        loadFactor = 0;
        table = new Entry<std::string,int>*[tableSize];

        for (int i = 0; i < tableSize; i++)
        {
            table[i] = nullptr;

        }
    }
    int getSize()
    {
        return tableSize;
    }

    int HashFunction(const Entry<std::string,int> entry)
    {
        return (entry.key.length() + entry.value) % tableSize; // puts values in range 0,1,2,3,4,5
    }

    int ProbingFunction(const int &x) // Must produce a cycle of length N to avoid causing an infinite loop.
    {
        // LINEAR PROBING, p(X) = ax , table size N, a and N must be relatively prime (GCD(a,N) = 1) to avoid infinite cycle.
        // P(x) = 1*x is a popular choice.
        return probingFactor*x;
    }

    void resizeTable()
    {
        // Resize table by doubling or tripling or exponentially to a size that maintains GCD(a,N) = 1.
        int oldTableSize = tableSize; // GCD(5, 12*2^i) = 1, for i = 0,1,2,3,... will always hold
        tableSize *= 2;
        Entry<std::string,int>** newTable = new Entry<std::string,int>*[tableSize];
        for (int i = 0; i < tableSize; i++)
        {
            newTable[i] = nullptr;

        }
        Entry<std::string,int>* tmp;
        for(int index=0; index < oldTableSize; index++)
        {
            if (table[index] != nullptr)
            {
                tmp = table[index];
                int x = 1;
                int keyHash = HashFunction(*tmp);
                int j = keyHash;
                while(newTable[j] != nullptr)
                {
                    j = (keyHash + ProbingFunction(x)) % tableSize;
                    x++;
                }
                newTable[j] = tmp;
            }
        }
        delete [] table;
        table = nullptr;

        table = newTable;

    }

    void Insert(const Entry<std::string, int> &entry)
    {
        if ( (itemsInTable+1) >= floor(tableSize*maxLoadFactor) )
            resizeTable();
        int x = 1;
        int keyHash = HashFunction(entry);
        int index = keyHash; 
 
        while(table[index] != nullptr && table[index]->tombstone != true) /// Use of tombstone in insert known as lazy deletion.
        {
            index = (keyHash + ProbingFunction(x)) % tableSize;
            x++;
        }

        Entry<std::string,int>* newEntry =  new Entry<std::string,int>();
        newEntry->key = entry.key;
        newEntry->value = entry.value;
        table[index] = newEntry;

        itemsInTable++;
        loadFactor = itemsInTable / tableSize;
    }

    Entry<std::string,int>* search(Entry<std::string, int> entry)
    {
        int x = 1;
        int keyHash = HashFunction(entry);
        int index = keyHash; 
        
        while(table[index] != nullptr && table[index]->key != entry.key)
        {
            index = (keyHash + ProbingFunction(x)) % DefaultTableSize;
            x++;
        }
        return table[index];
    }

    void remove(Entry<std::string, int> entry)
    {
        int x = 1;
        int keyHash = HashFunction(entry);
        int index = keyHash; 
        
        while(table[index] != nullptr && table[index]->key != entry.key)
        {
            index = (keyHash + ProbingFunction(x)) % DefaultTableSize;
            x++;
        }
        if (table[index] != nullptr)
        {
            table[index]->key = "-1"; // No name will ever be -1 therefore the loop will pass over the tomestone and search in the next spot.
            table[index]->tombstone = true;
        }
        // Else, element did not exist.
    }

    void printTable()
    {
        std::cout << "\n";
        Entry<std::string,int>* tmp;
        for (int i = 0; i < tableSize; i++)
        {
            tmp = table[i];
            if (tmp != nullptr)
                std::cout << *tmp << " ";
            else
                std::cout << " NIL ";
            if ((i+1) % 12 == 0)
                std::cout << "\n";
        }
    }

};


int main()
{
    HashTableLinearProbing ht;
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


    ht.Insert(p1);
    ht.Insert(p2);
    ht.Insert(p3);
    ht.Insert(p4);
    ht.Insert(p5);
    ht.Insert(p6);
    ht.Insert(p7);
    ht.Insert(p8);
    ht.Insert(p9);
    ht.Insert(p10);

    ht.printTable();

    int x;
    std::cin >> x;

}