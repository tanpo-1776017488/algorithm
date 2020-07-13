//#include <iostream>
//#include <time.h>
//#include <iomanip>
//#include <algorithm>
//#include <chrono>
//#include <assert.h>
//using namespace std;
//void show(int*arr, int size)
//{
//	for (int i = 0; i < size; i++)
//	{
//		cout << setw(4) << arr[i];
//		if ((i + 1) % 10 == 0)
//			cout << "\n";
//
//	}
//}
//void swap(int&num1, int&num2)
//{
//	int temp = num1;
//	num1 = num2;
//	num2 = temp;
//}
//void downheap(int cur, int k, int*heap)
//{
//	int left, right, p;//cur은 항상 down_heap 호출될때마다 0임
//	while (cur < k)//최대 힙 구성
//	{
//		left = cur * 2 + 1;//left_child
//		right = cur * 2 + 2;
//
//		if (left >= k && right >= k)
//			break;
//
//		p = cur;
//		if (left < k&&heap[p] < heap[left])
//			p = left;
//		if (right < k&&heap[p] < heap[right])//left와 right중 더 큰것 선택
//			p = right;
//		if (p == cur)//위의 2개 if 문을 지나면 p값이 변화가 있어야 하는데 없다?그러면 위치 변화가  더이상 필요없다는 의미.
//			break;
//
//		swap(heap[cur], heap[p]);
//		cur = p;
//	}
//}
//void heapify(int n, int*heap)
//{
//	int i, p;
//	for (int i = (n - 1) / 2; i >= 0; i--)//최소 절반은 해야함. 
//		downheap(i, n, heap);
//
//}
//void heap(int*heap, int size)
//{
//	//root 가 zero_version 
//	int k;
//	heapify(size, heap);//최대힙 만들기.
//
//	for (k = size - 1; k > 0; k--)//하나하나 다 down_heap  진행함.
//	{
//		assert(k != 0);
//
//		swap(heap[0], heap[k]);
//		downheap(0, k, heap);
//
//	}
//}
//int main()
//{
//
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL);
//	srand(time(NULL));
//	int size = 100;
//	bool *check = new bool[size]();
//	int*arr = new int[size]();
//	for (int i = 0; i < size; i++)
//	{
//		int temp_num = rand() % size;
//		while (check[temp_num] == true)
//			temp_num = rand() % size;
//		check[temp_num] = true;
//		arr[i] = temp_num;
//
//	}
//	cout << "before sorting \n";
//	show(arr, size);
//
//	auto start = chrono::system_clock::now();
//	heap(arr, size);
//	auto end = chrono::system_clock::now();
//
//	cout << "\n after sorting \n";
//	show(arr, size);
//
//	std::chrono::microseconds delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//	cout << "\n\n time :" << delta.count() << " microsecond ";
//
//}
