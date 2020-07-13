#include <iostream>
#include <math.h>
#include <algorithm>
#include <queue>
#define MAX_LENGTH INT_MAX/2-1
using namespace std;
const char name_city[12][5] = { "��õ","����","����","õ��","û��","����","����","����","����","�뱸","���","�λ�" };
/*
vertex�� ù��° index�� 0���
�����ڷ��� D[start][vertex_set-start]�� ���� �ڵ忡���� �ݴ�� ������(ǥ���� �ݴ�)
ex) 0 1 2 3 �� vertex�� �ִ�.�ּҰ�δ� 2->1->3->0->2 ���ΰ���
�����ڷῡ�� 1) D[2][11]�� �ּ� ��θ� ��Ÿ������ ���� �ڵ忡���� 2) D[2][4]�� �ּ�
1)�� ���� (bitmask)1011 �̰� 2)�� 0100��  ,ǥ���� ����

���� ������ �������� ���� ������ ��Ȥ Ʋ��ǥ���� ���� �� �ֽ��ϴ�.
*/
void find_v(int dis, int start, int**dist, int**path)
{
	queue<int> result;
	result.push(start);
	int new_start = start;
	int find_vari = 1 << start;
	//2�� for-loop�� �湮���� ����.
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (find_vari&(1 << j))
				continue;
			if (dis - dist[new_start][j] == path[j][find_vari + (1 << j)])//���� ���� �ǹ̴� �ѰŸ����� current position to j�� �� �Ÿ�,�� j���� ����� vertex�� subset�� distance�� ���� ����.
			{
				result.push(j);
				dis = path[j][find_vari + (1 << j)];
				//�� �ึ�� �ϳ����� ������ ������(�Ÿ��� ������ �ٸ� ��� ��������)
				new_start = j;
				find_vari += (1 << j);
			}
		}

	}
	while (!result.empty())
	{
		cout << name_city[result.front()] << " -> ";
		result.pop();
	}

}
bool isp(int check, int pos)//�湮�Ͽ����� checking
{
	if (check&(1 << pos))
		return true;
	return false;
}
int check_flag(int check, int pos)
{
	int new_check;
	new_check = check | (1 << pos);
	return new_check;
}
int TSP(int**dist, int check, int cur, int**path, int target)
{
	if (check == (1 << 12) - 1)//��� �湮 �ߴ���?
	{
		path[cur][check] = dist[cur][target];
		return dist[cur][target];
	}
	//���� ������ ���տ��� ���������� �Ÿ�,0�� ������ �׽��� �ҷ��� ���Ѱ��� target�� �ٲ�� ���������� ����
	if (path[cur][check] != 0)
		return  path[cur][check];//memozation
	 //else�� ��쿡 value�� 0�̴ϱ� ū ������ Ű������
	path[cur][check] = MAX_LENGTH;

	for (int i = 0; i < 12; i++)
	{
		//�̹̹湮�� vertex�� ���ܽ�Ŵ.
		if (isp(check, i))
			continue;
		if (dist[cur][i] == 0 || dist[cur][i] == MAX_LENGTH)//�ƿ� ���ɼ� ���� ������ �̸����� ����.
			continue;
		path[cur][check] = std::min(path[cur][check], TSP(dist, check_flag(check, i), i, path, target) + dist[cur][i]);

	}
	return  path[cur][check];
}
int** make_arr(int size)
{
	int**arr = new int*[12];
	int n = pow(2, 12);
	for (int i = 0; i < 12; i++)
		arr[i] = new int[n]();

	return arr;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int city;
	int start_v;
	int edge;
	cout << "������ ���� �������� �Է��Ͻÿ� : ";
	cin >> city >> start_v;
	int**vertex = new int*[city];
	int**path_info = new int*[city];
	int**sec_info = new int*[city];
	int n = pow(2, city);
	for (int i = 0; i < city; i++)
	{
		vertex[i] = new int[city]();
		path_info[i] = new int[n]();//n-1 index���� ���ٰ����ϱ� ����.
		sec_info[i] = new int[n]();
	}

	for (int i = 0; i < city; i++)
		for (int j = 0; j < city; j++)
			if (i != j)
				vertex[i][j] = MAX_LENGTH;
	//INT_MAX�������ϴϱ� �������� ���� ������ ���� �߻��Ͽ� ���ݰ� ���


	
	cout << "����� ���� �Է��Ͻÿ� :";
	cin >> edge;
	for (int i = 0; i < edge; i++)
	{
		int v1, v2, w;
		cin >> v1 >> v2 >> w;
		vertex[v1][v2] = w;
	}



	
		
		pair<int, int> start;
		start = make_pair(start_v, 1 << start_v);
		int dis = TSP(vertex, start.second, start.first, path_info, start.first);
		cout << " min distance :" << dis << "\n";
		find_v(dis, start.first, vertex, path_info);
		cout << name_city[start.first] << "\n\n";

	

}