#include <iostream>

// Counting Sort is a stable method, 
//Stable: Numbers with the same value appear in the output array in the same order as they do in the input array.
void CountingSort(int A[], int n, int B[], int k)
{
    int C[k+1] {0};
    
    for (int j = 0; j < n; j++)
        C[A[j]] = C[A[j]] + 1;
    // Now C[i] contains the number elements equal to i.
    for (int i = 1; i <= k; i++)
        C[i] = C[i] + C[i-1];
    // Now C[i] contains the number of elements less than or equal to i.
    for (int j = n-1; j >= 0; j--)
    {
        B[C[A[j]]-1] = A[j]; // -1 is for zero-indexing
        C[A[j]] = C[A[j]]-1;
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
    int A[] = {2,5,3,0,2,3,0,3};
    int lenOfA = sizeof(A)/sizeof(A[0]);
    int B[lenOfA] {0};
    int k = 5;
    PrintArr(A, lenOfA);
    CountingSort(A, lenOfA, B, k);
    PrintArr(B, lenOfA);
    int x;
    std::cin >> x;
}