//poj3083 Children of the Candy Corn
//本题要点
//如何简洁地实现顺时针和逆时针移动
//从起点右优先搜索相当于从终点左优先搜索
//这个解法的深度优先相当于不停地向"下"挖直到终点

#include <cstdio>
#include <queue>
#include <iostream>
using namespace std;

#define MAX 50

char map[MAX][MAX];
bool marked[MAX][MAX];
int d[MAX][MAX];
int mov[4][2] = { { -1, 0}, { 0, 1}, { 1, 0 }, {0, -1} };
int rotDir;
int w, h, len;
int sX, sY, eX, eY;
bool findEnd;


void dfs(int x, int y, int tX, int tY, int dir)
{
	if (x == tX && y == tY) {
		findEnd = true;
		return;
	}
	int nX, nY;
	dir = (dir + 3) % 4;
	for (int i = dir; i < dir + 4; ++i) {
		nX = x + mov[i % 4][0];
		nY = y + mov[i % 4][1];
		if (nX >= 0 && nX < h && nY >= 0 && nY < w
			&& map[nX][nY] != '#') {
			++len;
			dir = i;
			dfs(nX, nY, tX, tY, dir);
			if (findEnd)
				return;
		}
	}
}

void bfs(int x, int y)
{
	int cX = x, cY = y;
	queue<int> qX, qY;
	qX.push(cX);
	qY.push(cY);
	marked[cX][cY] = true;
	d[cX][cY] = 1;
	while (!qX.empty() && !qY.empty()) {
		cX = qX.front();
		cY = qY.front();
		qX.pop();
		qY.pop();
		if (cX == eX && cY == eY)
			return;
		for (int i = 0; i < 4; ++i) {
			int nX = cX + mov[i][0];
			int nY = cY + mov[i][1];
			if (nX >= 0 && nX < h && nY >= 0 && nY < w
				&& map[nX][nY] != '#' && !marked[nX][nY]) {
				qX.push(nX);
				qY.push(nY);
				d[nX][nY] = d[cX][cY] + 1;
				marked[nX][nY] = true;
			}
		}
	}
}

int main()
{
	int cases;
	scanf("%d", &cases);
	for (int i = 1; i <= cases; ++i) {
		//read map
		scanf("%d %d", &w, &h);
		for(int i = 0; i < h; ++i)
			for (int j = 0; j < w; ++j) {
				cin >> map[i][j];
				if (map[i][j] == 'S') {
					sX = i;
					sY = j;
				}
				if (map[i][j] == 'E') {
					eX = i;
					eY = j;
				}
			}
		//dfs, anticlockwise
		len = 1;
		findEnd = false;
		rotDir = 1;
		dfs(sX, sY, eX, eY, 0);
		cout << len << ' ';
		//dfs, clockwise
		len = 1;
		findEnd = false;
		rotDir = -1;
		dfs(eX, eY, sX, sY, 0);
		cout << len << ' ';
		//bfs, shortest path
		findEnd = false;
		for (int i = 0; i < h; ++i)
			for (int j = 0; j < w; ++j) {
				marked[i][j] = false;
				d[i][j] = -1;
			}
		bfs(sX, sY);
		cout << d[eX][eY] << endl;
	}
	return 0;
}
