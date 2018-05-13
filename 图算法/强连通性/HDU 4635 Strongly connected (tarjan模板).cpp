// Tarjan�㷨��ǿ��ͨ����
// �����˼·�ǣ����Ǳ����������ܶ������ǿ��ͨͼ�������뵽������Ȼ��������ǿ��ͨ�������ɣ�����ȫͼɾ�߶��ã�
// ��������ǿ��ͨ����Ķ������ΪX��Y (Y = N - X)
// ��ô�����ΪE = X(X - 1) + Y(Y - 1) + XY = N(N -1 ) - X(N - X)
// ҪʹE�����ܴ���ôX��Ҫ������С��
// �ص����⣬���Ǿ���Ҫ�Ѹ���ͼ����ǿ��ͨ������Ȼ���ҵ�ֻ����Ȼ�����Ұ�������������ٵ���ͨ����X��
// Ȼ���ʣ�µ���ͨ�������ɵ�Y���ɴ˹��ɵ�ͼ��������ǿ��ͨͼ��
// ��������Ҫ��ӵı�����E - M��

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
	if (dfn[u] == low[u]) {		//����ǿ��ͨ����
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