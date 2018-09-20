#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#define DataType int

void Swap(int* a, int* b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
void Print(DataType* arr, int len)
{
	assert(arr);
	int i;
	for (i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void BubbleSort(DataType* arr, int len)          //
{
	assert(arr);
	int i, j;
	for (i = 0; i < len - 1; i++)               //只需len-1趟
	{
		int flag = 0;
		for (j = 0; j < len - 1 - i; j++)       //每次从第一个元素开始判断,
		{
			if (arr[j]>arr[j + 1])
			{
				flag = 1;
				Swap(&arr[j], &arr[j + 1]);
			}
		}
		if (flag == 0)                        //标记
			return;
	}
}

void SelectSort(DataType* arr, int len)
{
	assert(arr);
	int i, j, min;
	for (i = 0; i < len - 1; i++)
	{
		min = i;
		for (j = i+1; j < len; j++)
		{
			if (arr[j]<arr[min])
			{
				min = j;
			}
		}
		if (i != min)
		{
			Swap(&arr[i], &arr[min]);
		}
	}
}

void SelectSortOS(DataType*arr, int len)
{
	assert(arr);
	int start = 0;
	int end = len - 1;
	int i;
	while (start < end)
	{
		int min=start;
		int max = end;
		for (i = start; i <= end; i++)
		{
			if (arr[min]>arr[i])
			{
				min = i;
			}
			if (arr[max] < arr[i])
			{
				max = i;
			}
		}
		if (max != end)
		{
			Swap(&arr[max], &arr[end]);
		}
		if (min == end)
		{
			min = max;
		}
		if (min != start)
		{
			Swap(&arr[min], &arr[start]);
		}
		start++;
		end--;
	}
}
void QuickSort(DataType* arr, int start,int end)
{
	assert(arr);
	DataType key = arr[start];
	int i = start;
	int j = end;
	if (start >= end)
		return;
	while (i != j)
	{
		while (i<j && arr[j] >= key)
			j--;
		while (i<j && arr[i] <= key)
			i++;	
		Swap(&arr[i], &arr[j]);
	}
	Swap(&arr[i], &arr[start]);
	QuickSort(arr, start, i - 1);
	QuickSort(arr, i + 1, end);
}

void AdjustDown(DataType* arr, int len, int parent)
{
	assert(arr);
	int child = parent * 2 + 1;
	while (child < len)
	{
		if ((child+1)<len && arr[child] < arr[child + 1])
			child++;
		if (arr[parent] < arr[child])
		{
			Swap(&arr[parent], &arr[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(DataType* arr, int len)              //堆排序
{
	assert(arr);
	int i = 0;
	int end = len - 1;
	for (i = (len - 2) / 2; i >= 0; i--)
	{
		AdjustDown(arr, len, i);
		Print(arr, len);
	}
	while (end > 0)
	{
		Swap(&arr[0], &arr[end]);
		AdjustDown(arr, end, 0);
		end--;
	}
}

void InsertSort(DataType* arr, int len)
{
	assert(arr);
	int i, j;
	DataType tmp;
	for (i = 1; i < len; i++)
	{
		j = i - 1;
		tmp = arr[i];
		while (j>=0 && tmp < arr[j])
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = tmp;
		Print(arr, len);
	}
}

void Merge(DataType* arr, int left, int mid, int right)
{
	assert(arr);
	int i, j, k, n1, n2;
	n1 = mid - left + 1;                  //左边元素个数
	n2 = right - mid;					  //右边元素个数
	DataType* front, *back;
	front = (DataType*)malloc(n1*sizeof(arr[0]));    
	back = (DataType*)malloc(n2*sizeof(arr[0]));
	for (i = 0; i < n1; i++)
		front[i] = arr[left + i];          //将左边数组元素放在新空间中
	for (j = 0; j < n2; j++)
		back[j] = arr[mid + 1 + j];        //将右边数组元素放在新空间中
	i = 0;
	j = 0; 
	k = left;							   //标记原始数组
	while (i < n1&&j < n2)
	{
		if (front[i] < back[j])            //合并排序，放入原数组中
			arr[k++] = front[i++];
		else
			arr[k++] = back[j++];
	}
	while (i < n1)                        
		arr[k++] = front[i++];
	while (j < n2)
		arr[k++] = back[j++];
	free(front);
	free(back);
}

void MergeSort(DataType* arr,int left,int right)
{
	assert(arr);
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;                //分成两组
		MergeSort(arr, left, mid);               //排左边的
		MergeSort(arr, mid + 1, right);			 //排右边的
		Merge(arr, left, mid, right);            //合并
	}
}

void ShellSort(DataType* arr, int len)
{
	assert(arr);
	int gap = 0;
	int i = 0;
	int j = 0;
	for (gap = len / 2; gap > 0; gap /= 2)     //增量gap
	{
		for (i = gap; i < len; i++)
		{
			j = i - gap;
			int tmp = arr[i];
			while(j >= 0 && arr[j] > tmp)
			{
				arr[j + gap] = arr[j];
				j -= gap;
			}
			if (j != i - gap)
				arr[j + gap] = tmp;
		}
		Print(arr, len);
	}
}
//void ShellSort(DataType* arr, int len)
//{
//	for (int gap = len / 2; gap > 0; gap /= 2)
//	{
//		//从第gap个元素，逐个对其所在组进行直接插入排序操作
//		for (int i = gap; i < len; i++)
//		{
//			int j = i;
//			while (j  >= 0 && arr[j] < arr[j-gap])
//			{
//				//插入排序采用交换法
//				Swap(&arr[j], &arr[j-gap]);
//				j -= gap;
//			}
//		}
//		Print(arr, len);
//	}
//}
void test()
{
	DataType arr[] = { 21, 18, 20, 25, 67, 20, -9,0};
	//DataType arr[] = {5,4,3,9,1,0};
	size_t len = sizeof(arr) / sizeof(arr[0]);
	//BubbleSort(arr,len);
	//SelectSort(arr, len);
	//SelectSortOS(arr, len);
	//QuickSort(arr, 0, len - 1);
	//HeapSort(arr, len);
	//InsertSort(arr, len);
	//MergeSort(arr, 0, len-1);
	ShellSort(arr, len);
	Print(arr, len);
}

int main()
{
	test();
	return 0;
}