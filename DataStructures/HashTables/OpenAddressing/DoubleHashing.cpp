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

bool isPrime(int n)
{
    // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;
   
    // This is checked so that we can skip 
    // middle five numbers in below loop
    if (n%2 == 0 || n%3 == 0) return false;
   
    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
           return false;
   
    return true;
}
 
// Function to return the smallest
// prime number greater than N
int nextPrime(int N)
{
 
    // Base case
    if (N <= 1)
        return 2;
 
    int prime = N;
    bool found = false;
 
    // Loop continuously until isPrime returns
    // true for a number greater than n
    while (!found) {
        prime++;
 
        if (isPrime(prime))
            found = true;
    }
 
    return prime;
}

const int DefaultTableSize = 7; // Table Size must be a prime number.
class HtDoubleHashing
{
    private:
    int tableSize;
    int itemsInTable;
    float maxLoadFactor;
    float loadFactor;
    Entry<std::string,int>** table;

    public:
    HtDoubleHashing()
    {

        maxLoadFactor = 0.35;
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

    int H1(const Entry<std::string,int> entry)
    {
        return (entry.key.length() + entry.value) % tableSize;
    }

    int H2(const Entry<std::string,int> entry)
    {
        return (entry.key.length() - entry.value) % tableSize;
    }

    int ProbingFunc(int x, int y)
    {
        return x*y;
    }

    void resizeTable()
    {
       // Tablesize must remain a prime
        int oldTableSize = tableSize;
        tableSize *= 2;

        // Find next prime number
        tableSize = nextPrime(tableSize);

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
                int x = 0;
                int keyHash1 = H1(*tmp);
                int keyHash2 = H2(*tmp);
                int delta = keyHash2 % tableSize;
                if (delta == 0) // Prevent infinite loop.
                    delta = 1; 
                int j = (keyHash1 + ProbingFunc(x,delta)) % tableSize;
                while(newTable[j] != nullptr)
                {
                    x++;
                    j = (keyHash1 + x*delta) % tableSize; // x*delta is the probing function x*H2(k)
                }
                newTable[j] = tmp;
            }
        }
        delete [] table;
        table = nullptr;

        table = newTable;
        loadFactor = itemsInTable / tableSize;
    }

    void Insert(const Entry<std::string, int> &entry)
    {
        if ( itemsInTable >= floor(tableSize*maxLoadFactor) )
            resizeTable();
        
        int x = 0;
        int keyHash1 = H1(entry);
        int keyHash2 = H2(entry);
        int delta = keyHash2 % tableSize;
        if (delta == 0) // Prevent infinite loop.
            delta = 1; 
        int index = (keyHash1 + x*delta) % tableSize;
 
        while(table[index] != nullptr)
        {
            x++;
            index = (keyHash1 + ProbingFunc(x,delta)) % tableSize; // Probing function.
        }

        Entry<std::string,int>* newEntry =  new Entry<std::string,int>();
        newEntry->key = entry.key;
        newEntry->value = entry.value;
        table[index] = newEntry;

        itemsInTable++;
        loadFactor = itemsInTable / tableSize;
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
    HtDoubleHashing ht;
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