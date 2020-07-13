#include <iostream>
#include <queue>


using namespace std;
int prim(deque<pair<int, int>>*map, int start, int vertex)
{
	bool *check = new bool[vertex + 1]();
	priority_queue<pair<int, int>, deque<pair<int, int>>, greater<pair<int, int>>>que;
	que.push(make_pair(0, 1));
	int sum = 0;
	while (!que.empty())
	{
		int next = -1;
		int next_weight;
		while (!que.empty())
		{
			next = que.top().second;
			next_weight = que.top().first;
			if (check[next] == false)
			{
				que.pop();

				break;
			}
			que.pop();

		}
		if (check[next] == true)
			break;
		check[next] = true;
		sum += next_weight;
		for (auto edge : map[next])
		{
			int t = edge.second;
			if (check[t] == false)
				que.push(edge);

		}

	}
	return sum;
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
		cin >> contries >> plane;

		deque<pair<int, int>>*map = new deque<pair<int, int>>[contries + 1];
		for (int i = 0; i < plane; i++)
		{
			int v1, v2;
			int weight = 1;
			cin >> v1 >> v2;
			map[v1].push_back(make_pair(weight, v2));
			map[v2].push_back(make_pair(weight, v1));

		}
		cout << prim(map, 1, contries) << "\n";


	}
}