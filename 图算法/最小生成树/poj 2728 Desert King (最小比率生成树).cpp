//poj2728 Desert King
//要点：0-1动态规划，最小比率生成树

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

#define MAXN 1001
#define INF 0x7fffffff
#define NIL -1
#define EPS 1e-4

struct Node {
	int x, y, z;
} node[MAXN];

struct Edge {
	double w, c, d;	//weight, cost, distance
} edge[MAXN][MAXN];

int N;
double key[MAXN];
int pi[MAXN];
bool visited[MAXN];

double calcDis(int a, int b)
{
	int dx = node[a].x - node[b].x, dy = node[a].y - node[b].y;
	return sqrt((double)(dx * dx + dy * dy));
}

double PrimMST(double R)
{
	//初始化
	for (int i = 0; i < N; ++i) {
		edge[i][i].w = edge[i][i].c = edge[i][i].d = 0;
		for (int j = i + 1; j < N; ++j) {
			edge[i][j].c = edge[j][i].c = fabs((double)(node[i].z - node[j].z));
			edge[i][j].d = edge[j][i].d = calcDis(i, j);
			edge[i][j].w = edge[j][i].w = edge[i][j].c - R * edge[i][j].d;
		}
	}
	//Relax源
	int s = 0;
	memset(visited, 0, sizeof(visited));
	for (int v = 0; v < N; ++v)
		key[v] = edge[s][v].w;
	for (int i = 0; i < N; ++i)
		pi[i] = s;
	pi[s] = NIL;
	visited[s] = true;
	//开始循环
	double totalCost = 0, totalDist = 0;
	for (int ctr = 1; ctr < N; ++ctr) {
		double min = INF;
		int u = -1;
		for (int i = 0; i < N; ++i)
			if (!visited[i] && key[i] < min) {
				min = key[i];
				u = i;
			}
		visited[u] = true;
		totalCost += edge[pi[u]][u].c;
		totalDist += edge[pi[u]][u].d;
		for (int v = 0; v < N; ++v)
			if (!visited[v] && edge[u][v].w < key[v]) {
				key[v] = edge[u][v].w;
				pi[v] = u;
			}
	}
	return totalCost / totalDist;
}

int main()
{
	while (cin >> N) {
		if (!N)
			break;
		for (int i = 0; i < N; ++i)
			scanf("%d %d %d", &node[i].x, &node[i].y, &node[i].z);
		double R = 0.0, nR = 100.0;
		while (fabs(R - nR) > EPS) {
			R = nR;
			nR = PrimMST(R);
		}
		printf("%.3lf\n", nR);
	}
	return 0;
}
