#include <iostream>
#include <algorithm>


int AllocateObject(int arr[], int &free) // pops off the stack of the free linked-list.
{
    int x;
    if (free == -2) // sentinel value.
        throw std::overflow_error("out of memory");
    else{
        x = free;
        free = arr[x+1];
        return x;
    }
};

void freeObject(int arr[], int &free, const int x) // push on to the stack of the free linked list.
{
    arr[x+1] = free;
    free = x;
};

void insert(int arr[],int &L, int &free, const int x)
{
    
    if (arr[L] == -1)
    {
        arr[L] = x;
        arr[L+1] = -1; // next
        arr[L+2] = -1; // prev
    } else {

        int newHead = AllocateObject(arr,free);
        arr[newHead] = x;
        arr[newHead+1] = L;
        arr[newHead+2] = -1;
        arr[L+2] = newHead;
        L = newHead;

    }
};

int ListSearch()
{
    // YET TO BE IMPLEMENTED.
}

void ListDelete() 
{
    // YET TO BE IMPLEMENTED.
}

void PrintArr(int A[], int lenOfA)
{
    for (int i = 0; i < lenOfA; i++)
    {
        std::cout << A[i] << " ";
    }
    std::cout << "\n";
}


int main()
{
    const int N(24);
    int free(0);
    int A[N] {0};
    // Initalize free singely linked list that acts as stack for doubly linked list.
    for (int i = 1; i < N; i += 3)
    {
        if ((i+3) > N)
            A[i] = -2; // Sentinel value.
        else {
            A[i] = i+2;
        }
    }
    
    PrintArr(A,N);
    int L = AllocateObject(A,free); // List head.
    A[L] = -1; // Doesn't hold data yet.
    insert(A,L,free,9);
    insert(A,L,free,7);
    insert(A,L,free,4);
    insert(A,L,free,1);
    insert(A,L,free,3);
    insert(A,L,free,2);
    insert(A,L,free,6);
    insert(A,L,free,5);
    // insert(A,L,free,5); // Throws error as it should.

    //freeObject(A,free,0); // Remove the last element in the linked list which is 9.
    //insert(A,L,free,5);

    PrintArr(A,N);

    

    int k;
    std::cin >> k;
}