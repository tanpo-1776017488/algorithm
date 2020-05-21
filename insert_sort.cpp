//#include <iostream>
//
//작은것을 기준으로 생각함
// complexity
//  
//  Best:n
//   Avg:n^2
// Worst:n^2
//using namespace std;
//
//int main()
//{
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL);
//	int arr[10] = { 1,10,5,8,7,6,4,3,2,9 };
//
//	for (int i = 1; i < 10; i++)
//	{
//		int j = i;
//		while (j >= 1 && arr[j] < arr[j - 1])
//		{
//			int temp = arr[j];
//			arr[j] = arr[j - 1];
//			arr[j - 1] = temp;
//			j--;
//		}
//	}
//	
//	return 0;
//}