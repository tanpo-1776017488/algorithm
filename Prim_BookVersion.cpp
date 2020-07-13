#include <iostream>
#include <queue>

#define INF 1000000
using namespace std;
void show(int*arr, int size)
{
	for (int i = 1; i <= size; i++)
		if (arr[i] == INF)
			cout << "INF ";
		else
			cout << arr[i] << " ";
}
int prim(int**W, int size, int*near, int*distance, int start)
{

	int level = 1;
	int sum = 0;
	distance[start] = -1;
	for (int i = 0; i < size; i++)
	{
		cout << "\nnear of level " << level++ << "\n";
		show(near, size);
		cout << "\ndistance \n";
		show(distance, size);
		int vnear = -1;
		int min = INF;
		for (int j = 1; j <= size; j++)
		{
			if (distance[j] >= 0 && distance[j] <= min)
				min = distance[j], vnear = j;

		}
		if (vnear == -1)
			break;
		sum += distance[vnear];
		distance[vnear] = -1;
		for (int j = 1; j <= size; j++)
			if (W[j][vnear] < distance[j])//���� ����� node�� �������� �� ���������� �Ÿ� ����� �ʱ�ȭ��.
				distance[j] = W[j][vnear], near[j] = vnear;//�������� �� -1�� �����ϸ� ���Ե� ���� �Ÿ��� �ǵ帮�� ����
														//


	}
	return sum;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//�ʱ� �׷��� ���� �ܰ�
	int vertex, edge;
	cout << "input vertex and edge : ";
	cin >> vertex >> edge;
	deque<int>*map = new deque<int>[vertex + 1]();
	int**W = new int*[vertex + 1];
	for (int i = 1; i <= vertex; i++)
		W[i] = new int[vertex + 1]();

	for (int i = 1; i <= vertex; i++)
		for (int j = 1; j <= vertex; j++)
			if (i != j)
				W[i][j] = INF;

	int start = 1;//���� ����
	cout << "input vertex to vertex and weight : \n";
	for (int i = 0; i < edge; i++)
	{
		int v1, v2, weight;
		cin >> v1 >> v2 >> weight;
		W[v1][v2] = weight;
		W[v2][v1] = weight;
	}
	int*near = new int[vertex + 1]();
	int*distance = new int[vertex + 1]();//���� ����� ������ �ε���
	for (int i = 1; i <= vertex; i++)
		distance[i] = W[start][i], near[i] = start;
	int result = prim(W, vertex, near, distance, start);
	cout << "\n\n result : " << result;


}