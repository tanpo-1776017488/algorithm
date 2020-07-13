#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
void DepthSearch(int x, int dep, int*depth, bool*visit, deque<int>*list, int*parent)
{
	depth[x] = dep;
	visit[x] = true;
	for (auto edge : list[x])
	{
		if (visit[edge])
			continue;
		parent[edge] = x;//edge의 부모는 x
		DepthSearch(edge, dep + 1, depth, visit, list, parent);
	}
}
int FindParent(int x, int y, int*depth, int*parent)
{
	while (depth[x] != depth[y])
	{
		if (depth[x] > depth[y])
			x = parent[x];
		else
			y = parent[y];
	}
	if (x == y)
		return x;
	while (parent[x] != parent[y])
	{
		x = parent[x];
		y = parent[y];
	}
	return parent[x];
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	cin >> n;
	deque<int>*list = new deque<int>[n + 1]();
	int*parent = new int[n + 1]();
	int*depth = new int[n + 1]();
	bool*visit = new bool[n + 1]();
	for (int i = 0; i < n - 1; i++)
	{
		int v1, v2;
		cin >> v1 >> v2;
		list[v1].push_back(v2);
		list[v2].push_back(v1);

	}
	cin >> m;
	//root는 1번
	DepthSearch(1, 0, depth, visit, list, parent);
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		cout << FindParent(x, y, depth, parent) << "\n";
	}

}