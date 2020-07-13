#include <iostream>
#include <queue>
#include <bitset>

using namespace std;
int find(int*parent, int target)
{
	if (parent[target] == target)
		return target;
	int head = find(parent, parent[target]);
	parent[target] = head;
	return head;
}
bool Union(int x, int y, int*parent)
{
	x = find(parent, x);
	y = find(parent, y);
	if (x != y)
	{
		parent[x] = y;
		return true;
	}
	return false;
}
int*init(int size)
{
	int*arr = new int[size + 1]();
	for (int i = 1; i <= size; i++)
		arr[i] = i;
	return arr;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);


	int test;
	cin >> test;
	for (int t = 0; t < test; t++)
	{
		int contries, plane;
		cin >> contries >> plane;//vertex개수 와 edge개수
		int*parent = init(contries);
		int count = 0;
		for (int i = 0; i < plane; i++)
		{
			int v1, v2;
			cin >> v1 >> v2;
			if (Union(v1, v2, parent))
				count++;
		}
		cout << count << "\n";

	}
}