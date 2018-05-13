class UnionFind
{
public:
	UnionFind(int N) : p(new int[N]), rank(new int[N]) {
		for (int i = 0; i < N; ++i) {
			p[i] = i;		//the parent of root is itself
			rank[i] = 0;
		}
	}
	
	~UnionFind() {
		delete[] p;
		delete[] rank;
	}

	int find(int u) {
		if (u != p[u])
			p[u] = find(p[u]);
		return p[u];
	}

	void link(int u, int v) {
		if (rank[u] > rank[v])
			p[v] = u;
		else {
			p[u] = v;
			if (rank[u] == rank[v])
				++rank[v];
		}
	}

	void Union(int u, int v) { link(find(u), find(v)); }

	bool connected(int p, int q) { return find(p) == find(q); }

private:
	int *p;		//parent
	int *rank;
};

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <climits>
#include <algorithm>
using namespace std;

#define MAXSIZE 510
#define INF 0x7fffffff

int S, P;
int X[MAXSIZE], Y[MAXSIZE];
int edgesize;
struct Edge {
	int u, v;
	double w;
} edge[MAXSIZE * MAXSIZE];
double A[MAXSIZE * MAXSIZE];

void initialize()
{
	scanf("%d %d", &S, &P);
	for (int i = 0; i < P; ++i)
		scanf("%d %d", &X[i], &Y[i]);
	edgesize = 0;
	for (int i = 0; i < P; ++i) 
		for (int j = i + 1; j < P; ++j) {
			edge[edgesize].u = i;
			edge[edgesize].v = j;
			int dx = X[i] - X[j], dy = Y[i] - Y[j];
			edge[edgesize++].w = sqrt((double)(dx * dx + dy * dy));
		}
}

bool edgeCmp(Edge &x, Edge &y) { return x.w < y.w; }

double kruskalMST()
{
	UnionFind uf(P);
	sort(edge, edge + edgesize, edgeCmp);
	int end = 0;
	for(int i = 0; i < edgesize; ++i)
		if (!uf.connected(edge[i].u, edge[i].v)) {
			A[end++] = edge[i].w;
			uf.Union(edge[i].u, edge[i].v);
		}
	return A[end - S];
}

int main()
{
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		initialize();
		printf("%.2lf\n", kruskalMST());
	}
		
}