#include <iostream>
#include <utility>
#include <algorithm>
#include <experimental/random>

int Partition(int A[], int p, int r)
{
    int x = A[r];
    int i = p-1;
    for (int j = p; j <= r-1; j++)
        if (A[j] <= x)
        {
            i++;
            std::swap(A[i],A[j]);
        }
    std::swap(A[i+1], A[r]);
    return (i+1);
}   

void QuickSort(int A[], int p, int r)
{
    if (p<r)
    {
        int q = Partition(A,p,r);
        QuickSort(A,p,q-1);
        QuickSort(A,q+1,r);
    }
}


int RandomizedPartition(int A[], int p, int r)
{
    int i = std::experimental::randint(p,r);
    std::swap(A[r],A[i]);
    return Partition(A,p,r);
}


// By randomizing the pivot value the input array is permuted to make the average case running time most likely. 
// Defends against worst case.
void RandomizedQuickSort(int A[], int p, int r)
{
    if (p < r)
    {
        int q = RandomizedPartition(A,p,r);
        RandomizedQuickSort(A,p,q-1);
        RandomizedQuickSort(A,q+1,r);
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
    int A[] = {8,67,5,6,3,2,1,23,45,34,4};
    int lenOfA = sizeof(A)/sizeof(A[0]);
    PrintArr(A, lenOfA);
    QuickSort(A,0,lenOfA-1);
    PrintArr(A, lenOfA);

    int B[] = {8,67,5,6,3,2,1,23,45,34,4};
    int lenOfB = sizeof(B)/sizeof(B[0]);
    PrintArr(B, lenOfB);
    RandomizedQuickSort(B,0,lenOfB-1);
    PrintArr(B, lenOfB);

    int wait;
    std::cin >> wait;
}