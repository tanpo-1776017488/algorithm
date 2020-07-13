#include <iostream>
#include <queue>

#define INF 1000000
using namespace std;
typedef pair<int, pair<int, int>> Edge;

void show(int*arr, int size)
{
	for (int i = 1; i <= size; i++)
	{
		if (arr[i] == INF)
			cout << "INF ";
		else
			cout << arr[i] << " ";
	}
}
void diijkstra(int n, int**W, int*touch, int*length, int start)
{


	length[start] = -1;
	int level = 1;
	for (int i = 0; i < n; i++)
	{
		int min = INF;
		cout << "\nlevel : " << level++;
		cout << "\n touch : \n";
		show(touch, n);
		cout << "\n length : \n";
		show(length, n);
		int vnear = -1;
		for (int j = 1; j <= n; j++)
		{
			if (0 <= length[j] && length[j] <= min)
			{
				min = length[j];
				vnear = j;
			}

		}
		if (vnear == -1)
			break;
		for (int j = 1; j <= n; j++)
		{
			if (length[vnear] + W[vnear][j] < length[j])
			{
				length[j] = length[vnear] + W[vnear][j];
				touch[j] = vnear;
			}
		}
		length[vnear] = -1;
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//방향 그래프 
	int vertex, edge;
	cout << "정점의 개수와 간선의 개수를 입력하시오 : ";
	cin >> vertex >> edge;
	int*touch = new int[vertex + 1]();
	int*length = new int[vertex + 1]();
	int start = 1;//시작 위치 바꾸기
	int**W = new int*[vertex + 1];
	for (int i = 1; i <= vertex; i++)
		W[i] = new int[vertex + 1]();

	for (int i = 1; i <= vertex; i++)
		for (int j = 1; j <= vertex; j++)
			if (i != j)
				W[i][j] = INF;
	for (int i = 0; i < edge; i++)
	{
		int v1, v2, weight;
		cin >> v1 >> v2 >> weight;
		W[v1][v2] = weight;

	}
	for (int i = 1; i <= vertex; i++)
		touch[i] = start, length[i] = INF;

	for (int j = 1; j <= vertex; j++)
		length[j] = W[start][j];

	diijkstra(vertex, W, touch, length, start);




}