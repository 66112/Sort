#include <bit.h>
void swap(int* a, int* b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
void QuickSort(int* arr, int left, int right)     //挖坑法
{
	int i = left;
	int j = right;
	int key = arr[i];
	if (left > right)
		return;
	while (i != j)
	{
		while (i<j && (arr[j] >= key))
			j--;
		while (i<j && (arr[i] <= key))
			i++;
		swap(&arr[i], &arr[j]);                 //交换大于key但在key前面的数
	}
	swap(&arr[left], &arr[i]);                  //一趟完后i=j,将key放在它应该在的位置上
	QuickSort(arr, left, i - 1);
	QuickSort(arr, i + 1, right);
}
//void QuickSort(int* arr, int left, int right)     //挖坑法
//{
//	if (arr[left] > arr[right])
//		swap(&arr[left], &arr[right]);
//	if ((left + 1) >= right)
//		return;
//	int key = (right - left - 1) / 3;
//	QuickSort(arr, left, right - key);
//	QuickSort(arr, left+key, right);
//	QuickSort(arr, left, right - key);
//
//}
int main()
{
	int i = 0;
	int arr[] = {21,18,20,25,67 };
	int left = 0;
	int right = sizeof(arr) / sizeof(arr[0]) - 1;
	QuickSort(arr, left, right);
	for (i = 0; i <= right; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}