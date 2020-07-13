#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int knap(int limit, int*wt, int*value, int n)
{
	int**arr = new int*[n + 1]();
	for (int i = 0; i <= n; i++)
		arr[i] = new int[limit + 1]();

	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= limit; j++)
		{
			if (i == 0 || j == 0)
				continue;
			if (wt[i - 1] <= j && j - wt[i - 1] >= 0)
				arr[i][j] = std::max(value[i - 1] + arr[i - 1][j - wt[i - 1]], arr[i - 1][j]);
			else
				arr[i][j] = arr[i - 1][j];
		}
	}
	return arr[n][limit];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int vertex, weight;
	cout << "보석의 수와 배낭의 무게 제한을 입력 하세요 : ";
	cin >> vertex >> weight;
	int*wt = new int[vertex + 1]();
	int*value = new int[vertex + 1]();
	cout << "각 보석의 무게와 값을 보석 수 만큼 입력 하세요 : \n";
	for (int i = 1; i <= vertex; i++)
		cin >> wt[i] >> value[i];
	cout << knap(weight, wt, value, vertex);
}