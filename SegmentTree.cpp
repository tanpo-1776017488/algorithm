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
	if (index > end || index < start)//out of range �̸� return
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
	int*tree = new int[4 * n]();//n�� 2�� �������̸� 2*n-1�Ҵ��ϸ� ������ �������̰� 4*n���� Ŀ������

	for (int i = 0; i < n; i++)
		cin >> number[i];

	init(tree, number, start, end, startNode);

	cout << "���� �� ������ �Է� �Ͻÿ�(range 1~N)  : ";
	cin >> left >> right;

	cout << Sum(tree, start, end, std::min(left - 1, right - 1), std::max(left - 1, right - 1), startNode);

	cout << "Update �� ������ ��ġ�� ��, ���� ���� ������ �Է��Ͻÿ� : ";
	cin >> modifyPosition >> modifyValue >> left >> right;

	Update(tree, modifyPosition - 1, start, end, startNode, modifyValue - number[modifyPosition - 1]);
	number[modifyPosition - 1] = modifyValue;

	cout << Sum(tree, start, end, std::min(left - 1, right - 1), std::max(left - 1, right - 1), startNode);

}