#include <iostream>
#include <queue>

#define INF 1000000
using namespace std;
typedef pair<int, pair<int, int>> Edge;

int find(int*parent, int target)
{
	if (parent[target] == target)
		return target;
	int head = find(parent, parent[target]);
	parent[target] = head;
	return head;
}
int*init(int SizeOfVertex)
{
	int*arr = new int[SizeOfVertex + 1]();
	for (int i = 1; i <= SizeOfVertex; i++)
		arr[i] = i;
	return arr;
}
bool merge(int*parent, int x, int y)
{
	int x_head = find(parent, x);
	int y_head = find(parent, y);

	if (x_head != y_head)
	{
		parent[x_head] = y_head;
		return false;
	}

	return true;
}
int kruskal(int vertex, priority_queue<Edge, deque<Edge>, greater<Edge>>&que)
{
	int count = 0;
	int*parent = init(vertex);
	int sum = 0;
	while (count < vertex - 1)
	{
		Edge cur = que.top();
		que.pop();
		if (!merge(parent, cur.second.first, cur.second.second))
		{
			sum += cur.first;
			count++;
		}

	}
	return sum;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int vertex, edge;
	cout << "정점의 개수와 간선의 개수를 입력하시오 : ";
	cin >> vertex >> edge;
	//deque<pair<int, int>>*map = new deque<pair<int, int>>[vertex + 1]();
	cout << "연결 정보의 그 간선의 가중치를 입력하세요 : \n";
	priority_queue<Edge, deque<Edge>, greater<Edge>>que;
	for (int i = 0; i < edge; i++)
	{
		int v1, v2, weight;
		cin >> v1 >> v2 >> weight;

		Edge tmp_info = make_pair(weight, make_pair(v1, v2));
		que.push(tmp_info);

	}
	int sum = kruskal(vertex, que);
	cout << sum;
}