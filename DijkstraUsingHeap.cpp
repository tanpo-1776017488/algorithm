#include <iostream>
#include <queue>
#define INF 2100000000
using namespace std;
void dijkstra(int start, int*dis, deque<pair<int, int>>*list, bool*check)
{
	dis[start] = 0;
	priority_queue<pair<int, int>, deque<pair<int, int>>, greater<pair<int, int>>>que;
	que.push(make_pair(0, start));
	while (!que.empty())
	{
		int cur_v = que.top().second;
		int distance = que.top().first;
		/*que.pop();
		if (dis[cur_v] < distance)
			continue;*/


		for (auto& edge : list[cur_v])
		{
			int new_cur = edge.second;
			int new_dis = distance + edge.first;
			if (dis[new_cur] > new_dis && !check[new_cur])
			{
				que.push(make_pair(new_dis, new_cur));
				dis[new_cur] = new_dis;
			}
		}
		check[cur_v] = true;
		que.pop();


	}
}
int main()
{

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int vertex, edge;
	cin >> vertex >> edge;
	int start;
	cin >> start;
	int*distance = new int[vertex + 1]();
	bool*check = new bool[vertex + 1]();
	for (int i = 1; i <= vertex; i++)
		distance[i] = INF;
	deque<pair<int, int>>*list_edge = new deque<pair<int, int>>[vertex + 1];

	for (int i = 0; i < edge; i++)
	{
		int v1, v2, w;
		cin >> v1 >> v2 >> w;
		list_edge[v1].push_back(make_pair(w, v2));
	}
	dijkstra(start, distance, list_edge, check);
	for (int i = 1; i <= vertex; i++)
	{
		if (distance[i] == INF)
			cout << "INF" << "\n";
		else
			cout << distance[i] << "\n";
	}

}