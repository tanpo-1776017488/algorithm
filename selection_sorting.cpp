#include <iostream>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int arr[10] = { 10,9,8,7,6,5,4,3,2,1 };

	for (int i = 0; i < 9; i++)
	{
		int min = arr[i];
		int min_index = i;
		for (int j = i + 1; j < 10; j++)
		{
			if (arr[i] > arr[j])
			{
				min_index = j;
				min = arr[j];
			}
		}
		if (min_index != i)
		{
			int temp = arr[i];
			arr[i] = min;
			arr[min_index] = temp;
		}
	}
	return 0;
}