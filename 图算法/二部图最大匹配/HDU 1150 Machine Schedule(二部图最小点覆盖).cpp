// hdu 1150 Machine Schedule
// 二部图最小点覆盖=最大匹配
#include <cstdio>
#include <cstring>
#include <list>
using namespace std;

#define MAX 105

int N, M, K;
list<int> adj[MAX];
int match[MAX];
bool marked[MAX];

bool dfs(int u)
{
	for (list<int>::iterator iter = adj[u].begin();
		iter != adj[u].end(); ++iter) {
		int v = *iter;
		if (!marked[v]) {
			marked[v] = true;
			if (match[v] == -1 || dfs(match[v])) {
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int main() {
	while (scanf("%d", &N) != EOF) {
		if (!N)
			break;
		scanf("%d %d", &M, &K);
		for (int i = 0; i < MAX; ++i)
			adj[i].clear();
		int x, y, z;
		for (int i = 0; i < K; ++i) {
			scanf("%d %d %d", &x, &y, &z);
			adj[y].push_back(z);
		}
		
		int times = 0;
		memset(match, 0xff, sizeof(match));
		for (int i = N; i >= 1; --i) {
			memset(marked, 0, sizeof(marked));
			if (dfs(i))
				times++;
		}
		printf("%d\n", times);
	}
	return 0;
}