#include<stdio.h>
#include<string.h>

#define INF 0x3f3f3f3f
#define MAXN 1005

int N, T, S, D;
int W[MAXN][MAXN];
bool visited[MAXN];
int dist[MAXN], target[MAXN];

void initialize()
{
	memset(W, 0x3f, sizeof(W));
	int a, b, c, m;
	N = 0;
	for (int i = 1; i <= T; i++) {
		scanf("%d%d%d", &a, &b, &c);
		if (W[a][b] > c)
			W[a][b] = W[b][a] = c;
		m = (a > b ? a : b);
		N = (m > N ? m : N);
	}
	int adj;
	for (int i = 1; i <= S; i++) {
		scanf("%d", &adj);
		W[0][adj] = W[adj][0] = 0;
	}
	for (int i = 1; i <= D; i++)
		scanf("%d", &target[i]);
}

void Dijkstra(int s)
{
	memset(visited, 0, sizeof(visited));
	memset(dist, 0x3f, sizeof(dist));
	dist[s] = 0;
	while (true) {
		int min = INF, u = -1;
		for (int i = 0; i <= N; i++)
			if (!visited[i] && dist[i] < min) {
				min = dist[i];
				u = i;
			}
		if (u == -1)
			return;
		visited[u] = 1;
		for (int v = 0; v <= N; v++)
			if (!visited[v] && dist[v] > dist[u] + W[u][v])
				dist[v] = dist[u] + W[u][v];
	}
}

int main()
{
	while (scanf("%d%d%d", &T, &S, &D) != EOF) {
		initialize();
		Dijkstra(0);
		int min = INF;
		for (int i = 1; i <= D; i++)
			if (dist[target[i]]<min)
				min = dist[target[i]];
		printf("%d\n", min);
	}
	return 0;
}