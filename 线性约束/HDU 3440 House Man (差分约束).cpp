// HDU 3440 House Man
// 差分约束

#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;

#define MAXN 1005
#define INF 0x3f3f3f3f

struct House {
	House() : id(0), height(0) {}
	House(int i, int h) : id(i), height(h) {}
	int id, height;
};

bool cmpHouse(const House &lhs, const House &rhs) {
	return lhs.height < rhs.height;
}

struct Edge{
	Edge(int t, int w) : to(t), weight(w) {}
	int to, weight;
};

int N, D;
House houses[MAXN];
list<Edge> adj[MAXN];
bool inQ[MAXN];
int d[MAXN], ctr[MAXN];

int SPFA(int s) {
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
			if (d[u] > d[v] + iter->weight) {
				d[u] = d[v] + iter->weight;
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


int main() {
	int T;
	scanf("%d", &T);
	for (int cases = 1; cases <= T; ++cases) {
		for (int i = 1; i <= N; ++i)
			adj[i].clear();
		scanf("%d %d", &N, &D);
		int height;
		for (int i = 1; i <= N; ++i) {
			scanf("%d", &height);
			houses[i] = House(i, height);
		}

		for (int i = 1; i <= N - 1; ++i)
			adj[i + 1].push_back(Edge(i, -1));
		sort(houses + 1, houses + N + 1, cmpHouse);
		for (int i = 1; i <= N - 1; ++i) {
			if (houses[i].id > houses[i + 1].id)
				adj[houses[i + 1].id].push_back(Edge(houses[i].id, D));
			else 
				adj[houses[i].id].push_back(Edge(houses[i + 1].id, D));
		}
		
		int s = std::min(houses[1].id, houses[N].id);
		int t = std::max(houses[1].id, houses[N].id);
		int ans;
		if (SPFA(s))
			ans = d[t];
		else
			ans = -1;
		printf("Case %d: %d\n", cases, ans);
	}
}