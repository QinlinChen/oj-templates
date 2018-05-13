// poj 3255 Roadblocks
// 用Dijkstra求次短路径

#include <list>
#include <cstdio>
using namespace std;

#define MAXN 5005
#define INF 0x70000000
int N, R;

struct Edge {
	Edge(int t, int w) : to(t), weight(w) {}
	int to, weight;
};

list<Edge> adj[MAXN];
int dist[MAXN][2];	//dist[][0]表示最短路，dist[][1]表示次短路   
bool visited[MAXN][2];

void dijkstra(int s)
{
	for (int i = 1; i <= N; ++i) {
		dist[i][0] = dist[i][1] = INF;
		visited[i][0] = visited[i][1] = false;
	}
	dist[s][0] = 0;
	
	// 同一条边可以经过多次，求解次短路，那么从A到B最多走两次  
	for (int ctr = 1; ctr <= 2 * N; ++ctr) {
		int u = -1, min = INF, type = 0;
		for (int i = 1; i <= N; ++i) {
			// 找到最短距离已经确定的点，从它出发更新相邻的点的最短路径
			// 再从最短距离出发确定次短距离
			if (!visited[i][0] && dist[i][0] < min) {
				// 最短路和次短路都更新 
				u = i;
				min = dist[i][0];
				type = 0;
			}
			else if (!visited[i][1] && dist[i][1] < min) {
				// 只更新次短路
				u = i;
				min = dist[i][1];
				type = 1;
			}
		}
		if (u == -1)
			break;
		visited[u][type] = true;

		for (list<Edge>::iterator it = adj[u].begin();
			it != adj[u].end(); ++it) {
			int to = it->to;
			int d = min + it->weight;
			if (d < dist[to][0]) {
				dist[to][1] = dist[to][0];
				dist[to][0] = d;
			}
			else if (d > dist[to][0] && d < dist[to][1]) {
				dist[to][1] = d;
			}
		}
	}
}

int main()
{
	while (scanf("%d %d", &N, &R) != EOF) {
		// initialize
		for (int i = 0; i < MAXN; ++i)
			adj[i].clear();
		int A, B, D;
		for (int i = 1; i <= R; ++i) {
			scanf("%d %d %d", &A, &B, &D);
			adj[A].push_back(Edge(B, D));
			adj[B].push_back(Edge(A, D));
		}

		dijkstra(1);
		printf("%d\n", dist[N][1]);
	}
	return 0;
}