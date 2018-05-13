// hdu 5102 The K-th Distance
// 把每个树的结点分别当成根进行bfs
// 搜满2k个结点，把深度之和除以二返回

#include <cstdio>
#include <list>
#include <assert.h>
#include <queue>
using namespace std;

#define MAXN 100005
typedef long long LL;

int N, K;
list<int> adj[MAXN];

struct Node {
	Node(int i, int p, int d) : idx(i), parent(p), depth(d) {}
	int idx;
	int parent;
	int depth;
};

void initialize()
{
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; ++i) 
		adj[i].clear();
	int u, v;
	for (int i = 1; i <= N - 1; ++i) {
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

LL bfs(int k)
{
	k *= 2;
	queue<Node> q;
	for (int i = 1; i <= N; ++i)
		q.push(Node(i, 0, 0));

	LL sum = 0;
	while (true) {
		assert(!q.empty());
		Node &node = q.front();
		for (list<int>::iterator iter = adj[node.idx].begin();
			iter != adj[node.idx].end(); ++iter) {
			int child = *iter;
			if (child != node.parent) {
				q.push(Node(child, node.idx, node.depth + 1));
				sum += node.depth + 1;
				if (--k == 0) {
					assert((sum & 0x1) == 0);
					return sum /= 2;
				}		
			}
		}
		q.pop();
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int cases = 1; cases <= T; ++cases) {
		initialize();
		printf("%ld\n", bfs(K));
	}
}