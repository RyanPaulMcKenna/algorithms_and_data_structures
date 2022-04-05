#include <iostream>
#include <math.h>       /* floor */
#include <stdlib.h> /* System */

const int TEN(10);

// Linked-List
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
}

void InsertionSort(Node* b)
{
    if (b != nullptr) {
        Node* i = nullptr;
        float key = 0;
        for (Node* j = b->next; j != nullptr; j = j->next)
        {
            //key = nums[j];
            key = j->data;

            i = j->prev;
            while (i != nullptr && i->data > key) // nums[i]
            {
                //nums[i+1] = nums[i];
                i->next->data = i->data;

                i = i->prev;
            }

            if (i == nullptr)
                i = b; // set back to base of list. Equivalent of (i+1)
            else
                i = i->next; // (i+1)

            //nums[i+1] = key;
            i->data = key;
        }
    }

}


void BucketSort(float A[])
{
    int n = 10;
    int i;
    int bIndex = 0;
    Node* B[n-1];
    for (i=0;i<n-1;i++)
        B[i] = nullptr;

    for (i = 1; i <= n; i++)
    {   
        bIndex = (int)(n*A[i-1]);
        insert( B[bIndex-1], A[i-1] );
    }

    for (i = 0; i < n-1; i++)
        InsertionSort(B[i]);

    //Concatenate the linked-lists B[0],B[1] ... B[n-1] together in order. 
    int j = 0;
    for(i = 0; i < n-1; i++)
    {
        if (B[i] != nullptr)
        {
            Node* tmp = B[i];
            while(tmp != nullptr)
            {
                A[j] = tmp->data;
                j++;
                tmp = tmp->next;
            }
        }
    }
}

void PrintArr(float A[], int lenOfA)
{
    for (int i = 0; i < lenOfA; i++)
    {
        std::cout << A[i] << " ";
    }
    std::cout << "\n";
}


int main() 
{
    Node* arr[2] {nullptr,nullptr};
    //Node* Bptr = nullptr;
    insert(arr[1], 0.74);
    insert(arr[1], 0.87);
    insert(arr[1], 0.31);
    insert(arr[1], 0.56);
    InsertionSort(arr[1]);
    std::cout << arr[1]->data << " " << arr[1]->next->data << " " << arr[1]->next->next->data << " " << arr[1]->next->next->next->data;
    std::cout << "\n----------------------------------------" << std::endl;
    
    // 0 <= A[i] < 1, for all i.
    float A[] = {0.78,0.17,0.39,0.26,0.72,0.94,0.21,0.12,0.23,0.68};
    PrintArr(A,TEN);
    BucketSort(A);
    PrintArr(A,TEN);


    int x;
    std::cin >> x;
}