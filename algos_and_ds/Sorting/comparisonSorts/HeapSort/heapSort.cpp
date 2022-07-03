#include <iostream>
#include <math.h>
#include <utility>      // std::swap
#include <cassert>
#include <algorithm>
#include <vector>

int parent(int i)
{
    // zero-indexed.
    if (i == 2)
        return 0;
    // should be floored but this is done automatically as integer data-type.
    return i >> 1;
}

int left(int i)
{
    // zero-indexed
    return 2*i + 1;
}
int right(int i)
{
    // zero-indexed
    return 2*i + 2;
}
void MaxHeapify(int A[], int heapSize, int i)
{

    int largest = i;
    int l = left(i);
    int r = right(i);
    if (l < heapSize && A[l] > A[i])
    {
        largest = l;
    }
    if (r < heapSize && A[r] > A[largest])
    {
        largest = r;
    }
    if (largest != i)
    {
        std::swap(A[largest], A[i]);
        MaxHeapify(A, heapSize,largest);
    }
}

void BuildMaxHeap(int A[], int lengthOfA)
{
    for (int i = floor(lengthOfA/2)-1; i >= 0; i--)
    {
        MaxHeapify(A,lengthOfA,i);
    }
}

void HeapSort(int A[], int lengthOfA)
{
    int heapSize = lengthOfA;
    BuildMaxHeap(A, lengthOfA);
    for (int i = heapSize-1; i >= 1; i--)
    {
        std::swap(A[0],A[i]);
        heapSize--;
        MaxHeapify(A, heapSize, 0);
        
    }
}

void PrintArr(int A[], int lenOfA)
{
    for (int i = 0; i < lenOfA; i++)
    {
        std::cout << A[i] << " ";
    }
    std::cout << "\n";
}

// Max-Priority queue (Max Heap implementation)
// All methods assume A is a max-heap.
int HeapMaximum(int A[])
{
    
    return A[1];
}

int HeapExtractMax(int A[], int lenOfA)
{
    int heapSize = lenOfA;
    assert(heapSize >= 1); // heap underflow.

    int max = A[1];
    A[1] = A[heapSize-1];

    heapSize--;

    MaxHeapify(A, heapSize, 0);
    return max;
}

void HeapIncreaseKey(int A[], int i, int key)
{
    assert(key >= A[i]); // Error: New key is smaler than current key.

    A[i] = key;
    while(i > 1 && A[parent(i)] < A[i])
    {
        std::swap(A[i],A[parent(i)]);
        i = parent(i);
    }
}

void MaxHeapInsert(int A[], int key, int lenOfA)
{
    int heapSize = lenOfA;
    std::vector<int> bigA(heapSize + 1);
    std::copy(A, A+heapSize, bigA.begin());

    // bigA[heapSize-1] = -100; , pretend -100 is negative infinity as no larger numbers are used in this example.
    bigA.push_back(-100);
    HeapIncreaseKey(A,heapSize,key);
}

int main()
{
    int A[] = {8,4,5,6,3,2,1,23,34,45,67};
    int lenOfA = sizeof(A)/sizeof(A[0]);
    PrintArr(A, lenOfA);
    HeapSort(A,lenOfA);
    PrintArr(A, lenOfA);
    
    std::cout << "Test priority queue.\n";

    std::cout << "Heap-Maximum is:" << HeapMaximum(A) << std::endl;

    
}