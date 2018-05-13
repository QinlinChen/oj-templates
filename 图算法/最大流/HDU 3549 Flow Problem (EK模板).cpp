// 最大流的实现
// 模板的优化挺好的

#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define MAXN 20
#define INF 0x7f7f7f7f
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

int N, M;
int cap[MAXN][MAXN], flow[MAXN][MAXN];	//利用维护flow[u][v] = -flow[v][u]优化

int pi[MAXN], path_cap[MAXN];	//即时运算path capacity，同时也有标记是否访问的作用

bool bfs(int s, int t)
{
	memset(path_cap, 0, sizeof(path_cap));
	memset(pi, 0xff, sizeof(pi));
	path_cap[s] = INF;
	queue<int> Q;
	Q.push(s);
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		if (u == t)
			return true;
		for (int v = 1; v <= N; ++v)
			if (!path_cap[v] && (cap[u][v] > flow[u][v])) {
				path_cap[v] = MIN(path_cap[u], cap[u][v] - flow[u][v]);
				pi[v] = u;
				Q.push(v);
			}
	}
	return false;
}

int EdmondsKarp(int s, int t)
{
	memset(flow, 0, sizeof(flow));
	int maxflow = 0;
	while (bfs(s, t)) {
		for (int v = t; pi[v] != -1; v = pi[v]) {
			int u = pi[v];
			flow[u][v] += path_cap[t];
			flow[v][u] -= path_cap[t];
		}
		maxflow += path_cap[t];
	}
	return maxflow;
}

void input()
{
	scanf("%d %d", &N, &M);
	int u, v, c;
	memset(cap, 0, sizeof(cap));
	for (int i = 1; i <= M; ++i) {
		scanf("%d %d %d", &u, &v, &c);
		cap[u][v] += c;
	}
}

int main()
{
	int cases;
	scanf("%d", &cases);
	for (int i = 1; i <= cases; ++i) {
		input();
		printf("Case %d: %d\n", i, EdmondsKarp(1, N));
	}
}