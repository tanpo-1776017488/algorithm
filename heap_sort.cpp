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
//	int left, right, p;//cur�� �׻� down_heap ȣ��ɶ����� 0��
//	while (cur < k)//�ִ� �� ����
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
//		if (right < k&&heap[p] < heap[right])//left�� right�� �� ū�� ����
//			p = right;
//		if (p == cur)//���� 2�� if ���� ������ p���� ��ȭ�� �־�� �ϴµ� ����?�׷��� ��ġ ��ȭ��  ���̻� �ʿ���ٴ� �ǹ�.
//			break;
//
//		swap(heap[cur], heap[p]);
//		cur = p;
//	}
//}
//void heapify(int n, int*heap)
//{
//	int i, p;
//	for (int i = (n - 1) / 2; i >= 0; i--)//�ּ� ������ �ؾ���. 
//		downheap(i, n, heap);
//
//}
//void heap(int*heap, int size)
//{
//	//root �� zero_version 
//	int k;
//	heapify(size, heap);//�ִ��� �����.
//
//	for (k = size - 1; k > 0; k--)//�ϳ��ϳ� �� down_heap  ������.
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
