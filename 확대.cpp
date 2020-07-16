#include <iostream>
#include <queue>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int row, col, zrow, zcol;
	cin >> row >> col >> zrow >> zcol;

	char**map = new char*[row];
	for (int i = 0; i < row; i++)
		map[i] = new char[col]();

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			cin >> map[i][j];	//1,2로확대해서 출력함
	int newRow = row * zrow;
	int newCol = col * zcol;
	
	char**copymap = new char*[newRow];
	for (int i = 0; i < newRow; i++)
		copymap[i] = new char[newCol]();

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			for (int k = 0; k < zrow; k++)
			{
				for (int r = 0; r < zcol; r++)
				{
					copymap[i*zrow + k][j*zcol + r] = map[i][j];
				}
			}
		}
	}

	for (int i = 0; i < newRow; i++)
	{
		for (int j = 0; j < newCol; j++)
			cout << copymap[i][j];
		cout << "\n";
	}

	
}
