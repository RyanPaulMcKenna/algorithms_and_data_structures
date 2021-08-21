#include <iostream>
using namespace std;

void Merge(double A[], int start, int end)
{
    double temp[end + 1 - start];
    // Temporary array
    
    // Can calculate mid in this function
    int mid = start + (end - start) / 2;
    
    // i points to the start of left half
    // j points to the start of right half
    int i = start, j = mid + 1;
    
    // k points to the start of Temporary array
    int k = 0;
    
    // Pick smaller values from both the halves
    // And increment the pointers accordingly
    while(i <= mid && j <= end) {
        if(A[i] <= A[j]) {
            temp[k++] = A[i++];
        }
        else {
            temp[k++] = A[j++];
        }
    }
    
    // When there are elements still left in the first half
    while(i <= mid) {
        temp[k++] = A[i++];
    }
    
    // When there are elements still left in the second half
    while(j <= end) {
        temp[k++] = A[j++];
    }
    
    // Copy the contents of Temporary array into main array
    for(i = start, k = 0; i <= end; i++, k++) {
        A[i] = temp[k];
    }
}

void MergeSort(double A[], int start, int end)
{
    if (start < end)
    {
        size_t mid = start + (end - start) / 2;
        MergeSort(A, start, mid);
        MergeSort(A, mid + 1, end);
        Merge(A, start, end);
    }

}


int main() {
    
    double arr[] = {3.0, 1.0, 4.0, 2.1, 6.4, 3.1, 8.93};
    MergeSort(arr, 0, 6);
    for(int i = 0; i < 7; i++) {
        cout << arr[i] << " ";
    }
    
    return 0;
}