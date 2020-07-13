#include <iostream>
#include <algorithm>
#include <time.h>
using namespace std;
int binary_search_made(int*arr, int left, int right,int target)
{
	if (left <= right)
	{
		int mid = (left + right) / 2;
		if (arr[mid] == target)
			return mid;
		if (arr[mid] > target)
			return binary_search_made(arr, mid + 1, right, target);
		if (arr[mid] < target)
			return binary_search_made(arr, left, mid - 1, target);
	}
	return -1;
}
void show(int*arr, int size)
{
	cout << "\narray information : \n";
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << "\n\n";
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	srand(time(NULL));
	int N,target;
	cout << "input size of array and target 1 to number of size :";
	cin >> N;
	cin >> target;
	int *arr = new int[N]();
	for (int i = 0; i < N; i++)
	{
		arr[i] = rand() % N + 1;
	}
	sort(arr, arr + N);
	
	show(arr, N);
	int result = binary_search_made(arr, 0, N - 1, target);
	if (result == -1)
		cout << "not found";
	else
		cout << "position :" << result << " value :" << arr[result] << " real value :" << target;
}