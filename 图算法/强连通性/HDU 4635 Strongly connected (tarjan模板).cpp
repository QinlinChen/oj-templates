// Tarjan算法求强连通分量
// 本题的思路是：考虑边数量尽可能多的最大非强连通图，可以想到，它必然是由两个强连通分量构成（由完全图删边而得）
// 设这两个强连通分类的顶点个数为X和Y (Y = N - X)
// 那么边最多为E = X(X - 1) + Y(Y - 1) + XY = N(N -1 ) - X(N - X)
// 要使E尽可能大，那么X就要尽可能小。
// 回到这题，我们就是要把给的图缩成强连通分量，然后找到只有入度或出度且包含顶点个数最少的连通分量X。
// 然后把剩下的连通分量并成点Y。由此构成的图就是最大非强连通图。
// 所以我们要添加的边数是E - M。

#include <cstdio>
#include <cstring>
#include <list>
#include <stack>
#include <assert.h>
using namespace std;

#define MAXN 100005
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

int N, M;
list<int> adj[MAXN];
int id[MAXN], od[MAXN];

int dfn[MAXN], low[MAXN], scc[MAXN], ctr[MAXN];
stack<int> S;
bool in_stack[MAXN];
int dfs_num, scc_num;

void Tarjan(int u) {
	dfn[u] = low[u] = ++dfs_num;
	in_stack[u] = true;
	S.push(u);
	for (list<int>::iterator iter = adj[u].begin();
		iter != adj[u].end(); ++iter) {
		int v = *iter;
		if (!dfn[v]) {
			Tarjan(v);
			low[u] = MIN(low[u], low[v]);
		}
		else if (in_stack[v])
			low[u] = MIN(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {		//构成强连通分量
		in_stack[u] = false;
		scc[u] = ++scc_num;
		ctr[scc_num]++;
		while (S.top() != u) {
			scc[S.top()] = scc_num;
			ctr[scc_num]++;
			in_stack[S.top()] = false;
			S.pop();
		}
		S.pop();
	}
}

long long solve() 
{
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; ++i)
		adj[i].clear();
	int u, v;
	for (int i = 1; i <= M; ++i) {
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
	}
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(scc, 0, sizeof(scc));
	memset(ctr, 0, sizeof(ctr));
	memset(id, 0, sizeof(id));
	memset(od, 0, sizeof(od));
	memset(in_stack, 0, sizeof(in_stack));
	dfs_num = scc_num = 0;

	for (int u = 1; u <= N; ++u)
		if (!dfn[u])
			Tarjan(u);
	if (scc_num == 1)
		return -1;
	for (int u = 1; u <= N; ++u) {
		for (list<int>::iterator iter = adj[u].begin();
			iter != adj[u].end(); ++iter) {
			int scc_from = scc[u], scc_to = scc[*iter];
			if (scc_from != scc_to) {
				od[scc_from]++;
				id[scc_to]++;
			}
		}
	}
	long long ans = N * (N - 1) - M;
	int min = N;
	for (int i = 1; i <= scc_num; ++i)
		if (id[i] == 0 || od[i] == 0)
			min = MIN(min, ctr[i]);
	assert(min != N);
	return ans - min * (N - min);
}

int main()
{
	int cases;
	scanf("%d", &cases);
	for (int i = 1; i <= cases; ++i)
		printf("Case %d: %lld\n", i, solve());
}