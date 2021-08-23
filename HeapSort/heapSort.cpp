#include <iostream>
#include <math.h>
#include <utility>      // std::swap

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
int main()
{
    int A[] = {8,4,5,6,3,2,1,23,34,45,67};
    int lenOfA = sizeof(A)/sizeof(A[0]);
    PrintArr(A, lenOfA);
    HeapSort(A,lenOfA);
    PrintArr(A, lenOfA);
    
}