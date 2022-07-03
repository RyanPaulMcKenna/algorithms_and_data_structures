// C++ implementation of Radix Sort
#include <iostream>
 
const int TEN(10);

int getMax(int A[], int n)
{
    int mx = A[0];
    for (int i = 1; i < n; i++)
        if (A[i] > mx)
            mx = A[i];
    return mx;
}

void print(int A[], int n)
{
    for (int i = 0; i < n; i++)
        std::cout << A[i] << " ";
}

void CountingSort(int A[], int n, int digit)
{
    int B[n];
    int i, C[TEN] = { 0 };

    for (i = 0; i < n; i++)
        C[(A[i] / digit) % TEN]++;
 

    for (i = 1; i < TEN; i++)
        C[i] += C[i - 1];

    for (i = n - 1; i >= 0; i--) {
        B[C[(A[i] / digit) % TEN] - 1] = A[i];
        C[(A[i] / digit) % TEN]--;
    }
    

    // Copy the B Aay to A[], so that A[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        A[i] = B[i];
}
 

// Radix Sort
void radixSort(int A[], int n)
{

    int m = getMax(A, n);

    for (int digit = 1; m / digit > 0; digit *= TEN)
        CountingSort(A, n, digit);
}
 

 
int main()
{
    int A[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
    int n = sizeof(A) / sizeof(A[0]);
    
    // Function Call
    radixSort(A, n);
    print(A, n);
    
    int x;
    std::cin >> x;
}