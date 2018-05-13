// poj 3169 Layout
// 差分约束
// Bellman-Ford 或者 SPFA

#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <list>
using namespace std;

#define MAXN 1005
#define INF 0x3f3f3f3f

typedef struct {
	int to, w;
} Edge;

int N, MD, ML;
list<Edge> adj[MAXN];
bool inQ[MAXN];
int d[MAXN], ctr[MAXN];

int SPFA(int s)
{
	queue<int> Q;
	memset(d, 0x3f, sizeof(d));
	memset(inQ, 0, sizeof(inQ));
	memset(ctr, 0, sizeof(ctr));
	d[s] = 0;
	Q.push(s);
	inQ[s] = true;
	ctr[s]++;

	while (!Q.empty()) {
		int v = Q.front(); Q.pop(); inQ[v] = false;
		for (list<Edge>::iterator iter = adj[v].begin(); 
			iter != adj[v].end();  ++iter) {
			int u = iter->to;
			if (d[u] > d[v] + iter->w) {
				d[u] = d[v] + iter->w;
				if (!inQ[u]) {
					Q.push(u);
					inQ[u] = true;
					if ((++ctr[u]) > N)
						return 0;
				}
			}
		}
	}
	return 1;
}

int main()
{
	while (cin >> N >> ML >> MD) {
		for (int i = 1; i <= N; ++i) 
			adj[i].clear();
		Edge e;
		for (int i = 2; i <= N; ++i) {
			e.to = i - 1; e.w = 0;
			adj[i].push_back(e);
		}
		int A, B, D;
		for (int i = 1; i <= ML; ++i) {
			scanf("%d %d %d", &A, &B, &D);
			e.to = B; e.w = D;
			adj[A].push_back(e);
		}
		for (int i = 1; i <= MD; ++i) {
			scanf("%d %d %d", &A, &B, &D);
			e.to = A; e.w = -D;
			adj[B].push_back(e);
		}
		if (SPFA(1) == 0)
			cout << -1;
		else if (d[N] == INF)
			cout << -2;
		else
			cout << d[N];
		cout << endl;
	}
}