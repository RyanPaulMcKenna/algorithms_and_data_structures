#include <iostream>
#include <limits>

void PrintArray(double arr[], size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}
void Merge(double A[], size_t start, size_t mid, size_t end)
{
	size_t n1 = mid - start;
	size_t n2 = end - mid;
	size_t i = 0;
	size_t j = 0;

	double* left = new double[n1 + 1];
	double* right = new double[n2 + 1];

	for (; i < n1; i++)
	{
		left[i] = A[start + i];
	}
	for (; j < n2; j++)
	{

		right[j] = A[mid + j];

	}

	left[n1] = std::numeric_limits<double>::infinity();
	right[n2] = std::numeric_limits<double>::infinity();

	i = 0;
	j = 0;
	for (size_t k = start; k < end; k++)
	{
		if (left[i] <= right[j])
		{
			A[k] = left[i];
			i++;
		}
		else
		{
			A[k] = right[j];
			j++;
		}
	}

	delete[] left;
	delete[] right;

}

void MergeSort(double A[], size_t start, size_t end)
{
	if (start < end)
	{
		size_t mid = (start + end) / 2; // int type floors naturally.
		MergeSort(A, start, mid);
		MergeSort(A, mid + 1, end);
		Merge(A, start, mid, end);
	}

}
int main()
{
	double nums[] = { 5,2,4,7,1,3,2,6,8 };
	size_t nums_size = 9;
	PrintArray(nums, nums_size);
	MergeSort(nums, 0, nums_size);
	PrintArray(nums, nums_size);
}