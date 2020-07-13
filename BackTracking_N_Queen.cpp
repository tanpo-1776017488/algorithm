#include <iostream>
#include <map>
#include <queue>
using namespace std;
void show(int size,bool**map)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (map[i][j] == false)
				cout << "0 ";
			else
				cout << "Q ";
		}
		cout << "\n";
	}
	cout << "\n\n";
}
void DFS(bool*cross_lower, bool*cross_uper, int size, int cur_col, bool*row_check, int&result,bool**map)
{
	if (cur_col == size)
	{
		result++;
		show(size, map);
		return;
	}
	for (int row = 0; row < size; row++)
	{
		//대각 선상에 포함되지 않으면 진행
		if (row_check[row] == true)
			continue;
		//우 상향은 위치좌표 x,y더하기
		if (cross_uper[cur_col + row] == false && cross_lower[size - 1 + (cur_col - row)] == false)
		{
			row_check[row] = true;
			cross_uper[cur_col + row] = true;
			cross_lower[size - 1 + (cur_col - row)] = true;
			map[row][cur_col] = true;
			DFS(cross_lower, cross_uper, size, cur_col + 1, row_check, result,map);
			map[row][cur_col] = false;
			row_check[row] = false;
			cross_uper[cur_col + row] = false;
			cross_lower[size - 1 + (cur_col - row)] = false;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	cin >> N;
	bool*cross_lower = new bool[2 * N - 1]();
	bool*cross_uper = new bool[2 * N - 1]();
	bool*row_check = new bool[N]();
	int result = 0;
	bool**map = new bool*[N];
	for (int i = 0; i < N; i++)
		map[i] = new bool[N]();
	DFS(cross_lower, cross_uper, N, 0, row_check, result,map);
	cout << result;

}