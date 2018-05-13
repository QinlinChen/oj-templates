// poj 2253 Frogger
// 利用修改条件的Dijkstra算法
// Relax的条件是d[v] > max{d[u], w[u][v]}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

#define MAXN 205
#define INF 0x3f3f3f3f

struct {
	int x, y;
} point[MAXN];

int N;
double W[MAXN][MAXN];
double d[MAXN];
bool visited[MAXN];

double calcDis(int a, int b)
{
	int dx = point[a].x - point[b].x, dy = point[a].y - point[b].y;
	return sqrt((double)(dx * dx + dy * dy));
}

void frogDistance()
{
	for (int i = 1; i <= N; ++i) {
		W[i][i] = 0;
		for (int j = i + 1; j <= N; ++j)
			W[i][j] = W[j][i] = calcDis(i, j);
	}
	for (int i = 1; i <= N; ++i)
		d[i] = W[1][i];
	memset(visited, 0, sizeof(visited));
	visited[0] = true;

	for (int ctr = 1; ctr < N; ++ctr) {
		double min = INF;
		int u = -1;
		for(int i = 1; i <= N; ++i)
			if (!visited[i] && d[i] < min) {
				min = d[i];
				u = i;
			}
		if (u < 0)
			return;
		visited[u] = true;

		for (int v = 1; v <= N; ++v) {
			double max = (d[u] > W[u][v] ? d[u] : W[u][v]);
			if (!visited[v] && d[v] > max)
				d[v] = max;
		}
	}
}

int main()
{
	int cases = 0;
	while (cin >> N) {
		if (N == 0)
			break;
		for (int i = 1; i <= N; ++i)
			scanf("%d %d", &point[i].x, &point[i].y);
		frogDistance();
		printf("Scenario #%d\nFrog Distance = %.3f\n\n", ++cases, d[2]);
	}
}