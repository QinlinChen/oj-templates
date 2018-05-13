// POJ 1273 Drainage Ditches
// ���������

#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define MAXN 205
#define INF 0x7f7f7f7f
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

int N, M;
int cap[MAXN][MAXN], flow[MAXN][MAXN];	//����ά��flow[u][v] = -flow[v][u]�Ż�
int pi[MAXN], path_cap[MAXN];	//��ʱ����path capacity��ͬʱҲ�б���Ƿ���ʵ�����

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
		for (int v = 1; v <= M; ++v)
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
	int u, v, c;
	memset(cap, 0, sizeof(cap));
	for (int i = 1; i <= N; ++i) {
		scanf("%d %d %d", &u, &v, &c);
		cap[u][v] += c;
	}
}

int main()
{
	while (cin >> N >> M) {
		input();
		cout << EdmondsKarp(1, M) << endl;
	}
}