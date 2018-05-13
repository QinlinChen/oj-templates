//poj2488 A Knight's Journey
//本题要点
//熟悉dfs基本套路

#include <iostream>
#define SIZE 26
using namespace std;

int sX[SIZE][SIZE];	//(x,y)结点的后继结点的X
int sY[SIZE][SIZE];	//(x,y)结点的后继结点的Y
int moveX[8] = { -2, -2, -1, -1, +1, +1, +2, +2 };
int moveY[8] = { -1, +1, -2, +2, -2, +2, -1, +1 };
bool marked[SIZE][SIZE];
int ROW;
int COL;
bool getAns;

void printResult()
{
	int x = 0, y = 0;
	while (x != -1 && y != -1) {
		cout << (char)('A' + x) << (1 + y);
		int temp = sY[y][x];
		x = sX[y][x];
		y = temp;
	}
}

void dfs(int x, int y, int depth)
{
	if (getAns)
		return;
	if (depth == ROW * COL) {
		printResult();
		cout << '\n';
		getAns = true;
		return;
	}

	marked[y][x] = true;
	for (int i = 0; i < 8; ++i) {
		int nextX = x + moveX[i];
		int nextY = y + moveY[i];
		if (nextX >= 0 && nextX < COL
			&& nextY >= 0 && nextY < ROW && !marked[nextY][nextX]) {
			sX[y][x] = nextX;
			sY[y][x] = nextY;
			dfs(nextX, nextY, depth + 1);
			sX[y][x] = sY[y][x] = -1;
		}
	}
	marked[y][x] = false;
}

int main()
{
	int cases;
	cin >> cases;
	for(int i = 1; i <= cases; ++i) {
		cin >> ROW >> COL;
		for (int r = 0; r < ROW; ++r)
			for (int c = 0; c < COL; ++c) {
				marked[r][c] = false;
				sX[r][c] = sY[r][c] = -1;
			}
		getAns = false;
		cout << "Scenario #" << i << ":\n";
		dfs(0, 0, 1);
		if (!getAns)
			cout << "impossible" << '\n';
		cout << endl;
	}
	
	return 0;
}