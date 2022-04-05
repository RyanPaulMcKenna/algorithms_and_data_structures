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



int RandomizedPartition(int A[], int p, int r)
{
    int i = std::experimental::randint(p,r);
    std::swap(A[r],A[i]);
    return Partition(A,p,r);
}

// Select the ith smallest element.
int RandomizedSelect(int A[], int p, int r, int i)
{
    if (p==r)
        return A[p];
    int q = RandomizedPartition(A,p,r);
    int k = q - p + 1;
    if (i==k)
        return A[q];
    else if(i < k)
        return RandomizedSelect(A,p,q-1,i);
    return RandomizedSelect(A,q+1,r,i-k);
}

int main()
{
    int A[] = {6,3,8,1,5,4,9,2,7}; // All distinct.
    int n = sizeof(A)/sizeof(A[0]);
    // Find the 5th smallest value in the array.
    int i = RandomizedSelect(A,0,n-1,5);
    std::cout << i;
    int x;
    std::cin >> x;
}