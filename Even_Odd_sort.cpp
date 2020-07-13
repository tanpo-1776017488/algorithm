#include <iostream>
#include <time.h>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <assert.h>
using namespace std;
void show(int*arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << setw(4) << arr[i];
		if ((i + 1) % 10 == 0)
			cout << "\n";

	}
}
void swap(int&num1, int&num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
}
void even_odd(int*arr, int size)
{
	bool det = false;
	while (!det)
	{
		det = true;
		for (int i = 1; i < size - 1; i += 2)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
				det = false;
			}
		}
		for (int i = 0; i < size - 1; i += 2)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
				det = false;
			}
		}
	}
}
int main()
{

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	srand(time(NULL));
	int size = 100;
	bool *check = new bool[size]();
	int*arr = new int[size]();
	for (int i = 0; i < size; i++)
	{
		int temp_num = rand() % size;
		while (check[temp_num] == true)
			temp_num = rand() % size;
		check[temp_num] = true;
		arr[i] = temp_num;

	}
	cout << "before sorting \n";
	show(arr, size);

	auto start = chrono::system_clock::now();
	even_odd(arr, size);
	auto end = chrono::system_clock::now();

	cout << "\n after sorting \n";
	show(arr, size);

	std::chrono::microseconds delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "\n\n time :" << delta.count() << " microsecond ";

}
