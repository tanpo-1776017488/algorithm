//#include <iostream>
//#include <math.h>
//#include <time.h>
///*
//merit:very good Time complexicy
//fault:difficult to implement
//Time_complexity
//average:n*log n
//worst  :n^2
//initial pivot set to first index in array
//pivot value is seted random index
//
//*/
//using namespace std;
//void show(int *arr)
//{
//	for (int i = 0; i < 10; i++)
//		cout << arr[i] << " ";
//	cout << "\n";
//}
//void swap(int &num1, int& num2)
//{
//	int temp = num1;
//	num1 = num2;
//	num2 = temp;
//	
//}
//int partition(int *arr, int start, int end)
//{
//	srand(time(NULL));
//	int random = rand() % (end - start + 1) + start;
//	swap(arr[random], arr[end]);
//	int pivot = start;
//	for (int i = start; i < end; i++)
//	{
//		if (arr[i] <= arr[end])
//		{
//			swap(arr[i], arr[pivot]);
//			pivot++;
//		}
//	}
//	swap(arr[pivot], arr[end]);
//
//	return pivot;
//}
//void quick_sort(int*arr, int start, int end)//seperate and conquer
//{
//	if (start < end)
//	{
//		int index = partition(arr, start, end);
//		quick_sort(arr, start, index - 1);
//		quick_sort(arr, index + 1, end);
//
//	}
//}
//int main()
//{
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL);
//
//	int arr[10] = { 90,80,70,60,50,40,30,20,10,100 };
//	quick_sort(arr, 0, 9);
//	show(arr);
//
//}
