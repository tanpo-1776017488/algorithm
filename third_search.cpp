#include <iostream>

using namespace std;
int third_search(int low, int high, int*arr,int target)
{
	if (low <= high)
	{
		int mid1 = (low + high) / 3;
		int mid2 = (low + high) * 2 / 3;

		if (target == arr[mid1])
			return mid1;
		if (arr[mid2] == target)
			return mid2;

		if (target < arr[mid1])
			return third_search(low, mid1 - 1, arr, target);
		else if (target < arr[mid2])
			return third_search(mid1 + 1, mid2 - 1, arr, target);
		else
			return third_search(mid2 + 1, high, arr, target);



	}
	return -1;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);


}