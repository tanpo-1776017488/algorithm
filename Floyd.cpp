#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
using namespace std;
#define INF 1000000
void show(int**path, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (path[i][j] == INF)
				cout <<setw(4)<<"oo" ;
			else
				cout << setw(4) << path[i][j];
		}
		cout << "\n";
	}
	cout << "\n\n";
}
void floyd(int**arr, int**path, int size)
{

	for (int flag = 0; flag < size; flag++)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (arr[i][j] > arr[i][flag] + arr[flag][j])
				{
					arr[i][j] = arr[i][flag] + arr[flag][j];
					path[i][j] = flag;
				}
			}
		}
		cout << "flag :" << flag << "\n";
		show(arr, size);
	}

}
void find_vertex(int**path, int size, int start, int des, queue<int>&que,int&count)
{
	//중간노드 기준으로 앞 부분 구하기
	if (path[start][des] != 0)
	{
		count++;
		find_vertex(path, size, start, path[start][des], que,count);
		que.push(path[start][des]);
		find_vertex(path, size, path[start][des], des, que,count);
	}
	//중간노드 기준으로 뒷 부분 구하기.0
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int size = 5;
	int**arr = new int*[size];
	int**path = new int*[size];
	for (int i = 0; i < size; i++)
		arr[i] = new int[size](), path[i] = new int[size]();

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (i != j)
				arr[i][j] = INF;

	arr[0][1] = 5, arr[1][0] = 5, arr[0][2] = 3, arr[2][0] = 3, arr[0][3] = 13, arr[3][0] = 13;
	arr[1][2] = 7, arr[2][1] = 7, arr[1][3] = 2, arr[3][1] = 2, arr[1][4] = 8, arr[4][1] = 8;
	arr[2][3] = 5, arr[3][2] = 5,arr[2][4]=9,arr[4][2]=9;
	arr[3][4] = 1, arr[4][3] = 1;
	show(arr, size);

	floyd(arr, path, size);
	/*int start, end;
	queue<int>result;
	for (int i = 1; i < size; i++)
	{
		start = i;
		
		for (int j = 1; j < size; j++)
		{
			int count = 0;
			end = j;
			result.push(start);
			find_vertex(path, size, start, end, result,count);
			result.push(end);

			while (result.size() != 1)
			{
				cout << result.front() << " ->";
				result.pop();
			}

			cout << result.front();
			result.pop();
			cout << "  연산 횟수 :" << count;
			cout << "\n\n";
		}
	}
	*/
	


}


