#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 1002
#define INF 0x70000000

struct {
	bool has;
	int w, p;
} edge[MAXN][MAXN];

int N, M, S, T;
int dist[MAXN], cost[MAXN];
bool visited[MAXN];

void initialize()
{
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j) {
			edge[i][j].w = edge[i][j].p = INF;
			edge[i][j].has = false;
		}
	int u, v, d, p;
	for (int i = 1; i <= M; ++i) {
		scanf("%d %d %d %d", &u, &v, &d, &p);
		if (d < edge[u][v].w) {
			edge[u][v].w = edge[v][u].w = d;
			edge[u][v].p = edge[v][u].p = p;
			edge[u][v].has = edge[v][u].has = true;
		}
	}
	scanf("%d %d", &S, &T);
	for (int i = 1; i <= N; ++i) {
		dist[i] = cost[i] = INF;
		visited[i] = false;
	}
	dist[S] = cost[S] = 0;
}

void Dijkstra() 
{
	initialize();
	for (int ctr = 1; ctr <= N; ++ctr) {
		int u = -1, min = INF;
		for(int i = 1; i <= N; ++i)
			if (!visited[i] && dist[i] < min) {
				min = dist[i];
				u = i;
			}
		visited[u] = true;

		for (int v = 1; v <= N; ++v)
			if (!visited[v] && edge[u][v].has) {
				if (dist[v] > dist[u] + edge[u][v].w) {
					dist[v] = dist[u] + edge[u][v].w;
					cost[v] = cost[u] + edge[u][v].p;
				}
				else if (dist[v] == dist[u] + edge[u][v].w) {
					if(cost[v] > cost[u] + edge[u][v].p)
						cost[v] = cost[u] + edge[u][v].p;
				}
			}
	}
}

int main()
{
	while (cin >> N >> M) {
		if (N == 0 && M == 0)
			break;
		Dijkstra();
		cout << dist[T] << " " << cost[T] << endl;
	}
}