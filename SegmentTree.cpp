#include <iostream>
#include <algorithm>
using namespace std;
int init(int*tree, int*number, int start, int end, int node)
{
	if (start == end)
		return tree[node] = number[start];

	int mid = (start + end) / 2;
	return tree[node] = init(tree, number, start, mid, node * 2) + init(tree, number, mid + 1, end, node * 2 + 1);

}
int Sum(int*tree, int start, int end, int left, int right, int node)
{
	if (left > end || start > right)
		return 0;

	if (left <= start || end <= right)
		return tree[node];

	int mid = (start + end) / 2;
	return Sum(tree, start, mid, left, right, node * 2) + Sum(tree, mid + 1, end, left, right, node * 2 + 1);
}
void Update(int*tree, int index, int start, int end, int node, int diff)
{
	if (index > end || index < start)//out of range 이면 return
		return;

	tree[node] += diff;
	if (start == end)
		return;

	int mid = (start + end) / .2;
	Update(tree, index, start, mid, node * 2, diff);//leftSubtree Update
	Update(tree, index, mid + 1, end, node * 2 + 1, diff);

}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	int start = 0, end = n - 1, startNode = 1;
	int left, right;
	int modifyPosition, modifyValue;
	int*number = new int[n];
	int*tree = new int[4 * n]();//n이 2의 제곱수이면 2*n-1할당하면 되지만 범용적이게 4*n으로 커버가능

	for (int i = 0; i < n; i++)
		cin >> number[i];

	init(tree, number, start, end, startNode);

	cout << "구간 합 범위를 입력 하시오(range 1~N)  : ";
	cin >> left >> right;

	cout << Sum(tree, start, end, std::min(left - 1, right - 1), std::max(left - 1, right - 1), startNode);

	cout << "Update 할 원소의 위치와 값, 구간 합의 범위를 입력하시오 : ";
	cin >> modifyPosition >> modifyValue >> left >> right;

	Update(tree, modifyPosition - 1, start, end, startNode, modifyValue - number[modifyPosition - 1]);
	number[modifyPosition - 1] = modifyValue;

	cout << Sum(tree, start, end, std::min(left - 1, right - 1), std::max(left - 1, right - 1), startNode);

}