#include <iostream>

void InsertionSort(int nums[])
{
	int i = 0;
	int key = 0;
	for (int j = 1; j < 6; j++)
	{
		key = nums[j];
		i = j - 1;
		while (i > -1 && nums[i] > key)
		{
			nums[i+1] = nums[i];
			i = i - 1;
		}
		nums[i+1] = key;

	}
}

void PrintArray(int arr[]) 
{
	for (int i = 0; i < 6; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int main() {

	int nums[6] = {5,2,4,6,1,3};
	std::cout << "Insertion Sort" << std::endl;
	PrintArray(nums);
	InsertionSort(nums);
	PrintArray(nums);


	return 0;
}