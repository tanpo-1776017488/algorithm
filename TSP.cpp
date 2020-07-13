#include <iostream>
#include <math.h>
#include <algorithm>
#include <queue>
#define MAX_LENGTH INT_MAX/2-1
using namespace std;
const char name_city[12][5] = { "인천","서울","강릉","천안","청주","동해","대전","울진","광주","대구","울산","부산" };
/*
vertex의 첫번째 index는 0사용
강의자료의 D[start][vertex_set-start]은 이하 코드에서는 반대로 구현함(표현의 반대)
ex) 0 1 2 3 의 vertex가 있다.최소경로는 2->1->3->0->2 으로가정
강의자료에는 1) D[2][11]이 최소 경로를 나타내지만 이하 코드에서는 2) D[2][4]가 최소
1)의 경우는 (bitmask)1011 이고 2)는 0100임  ,표현의 차이

제가 이해한 바탕으로 만들어서 설명에서 간혹 틀린표현이 있을 수 있습니다.
*/
void find_v(int dis, int start, int**dist, int**path)
{
	queue<int> result;
	result.push(start);
	int new_start = start;
	int find_vari = 1 << start;
	//2중 for-loop로 방문순서 추적.
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (find_vari&(1 << j))
				continue;
			if (dis - dist[new_start][j] == path[j][find_vari + (1 << j)])//왼쪽 항의 의미는 총거리에서 current position to j를 뺀 거리,즉 j에서 출발한 vertex의 subset의 distance와 같다 우항.
			{
				result.push(j);
				dis = path[j][find_vari + (1 << j)];
				//각 행마다 하나씩만 조건을 충족함(거리가 같으면 다른 경로 생성가능)
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
bool isp(int check, int pos)//방문하였는지 checking
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
	if (check == (1 << 12) - 1)//모두 방문 했는지?
	{
		path[cur][check] = dist[cur][target];
		return dist[cur][target];
	}
	//가장 마지막 집합에서 시작점까지 거리,0은 임으로 테스팅 할려고 정한거지 target이 바뀌면 유동적으로 변함
	if (path[cur][check] != 0)
		return  path[cur][check];//memozation
	 //else의 경우에 value는 0이니까 큰 값으로 키워주자
	path[cur][check] = MAX_LENGTH;

	for (int i = 0; i < 12; i++)
	{
		//이미방문한 vertex는 제외시킴.
		if (isp(check, i))
			continue;
		if (dist[cur][i] == 0 || dist[cur][i] == MAX_LENGTH)//아예 가능성 없는 조합은 미리부터 버림.
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
	cout << "도시의 수와 시작점을 입력하시오 : ";
	cin >> city >> start_v;
	int**vertex = new int*[city];
	int**path_info = new int*[city];
	int**sec_info = new int*[city];
	int n = pow(2, city);
	for (int i = 0; i < city; i++)
	{
		vertex[i] = new int[city]();
		path_info[i] = new int[n]();//n-1 index까지 접근가능하기 때문.
		sec_info[i] = new int[n]();
	}

	for (int i = 0; i < city; i++)
		for (int j = 0; j < city; j++)
			if (i != j)
				vertex[i][j] = MAX_LENGTH;
	//INT_MAX값으로하니까 예상하지 못한 오류가 많이 발생하여 절반값 사용


	
	cout << "노드의 수를 입력하시오 :";
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