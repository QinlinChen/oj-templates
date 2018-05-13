// POJ 2404 Jogging Trails
// 要求是给图添加权重最的少边，形成最小权欧拉回路
// 先找出所有奇结点，然后对这些结点进行匹配(匹配边是两点间的最短路径)
// 用状态压缩+memoize搜索，找到最小匹配

#include <cstdio>  
#include <cstring>  
#include <algorithm>  

#define INF 0x3f3f3f3f
#define MAXN 16

int dist[MAXN][MAXN];
int dp[1 << MAXN], deg[MAXN], odd[MAXN];
int N, M, nr_odd;

void floyd_warshall() {
	for (int k = 1; k <= N; ++k)
		for (int i = 1; i <= N; ++i)
			for (int j = 1; j <= N; ++j)
				dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
}

int search(int stat) {
	if (stat == 0)
		return 0;
	if (dp[stat] != -1)
		return dp[stat];
	 
	int min_dist_match = INF;
	for (int i = 0; i < nr_odd; ++i) {
		if (stat & (1 << i)) {
			for (int j = i + 1; j < nr_odd; ++j) {
				if (stat & (1 << j)) {
					int tmp = search(stat - (1 << i) - (1 << j)) + dist[odd[i]][odd[j]];
					if (tmp < min_dist_match)
						min_dist_match = tmp;
				}
			}
		}
	}
	dp[stat] = min_dist_match;
	return dp[stat];
}

int main() {
	while (scanf("%d", &N) != EOF) {
		if (N == 0)
			break;
		scanf("%d", &M);

		memset(dist, 0x3f, sizeof(dist));
		memset(dp, -1, sizeof(dp));
		memset(deg, 0, sizeof(deg));

		int sum = 0;
		for (int i = 1; i <= M; ++i) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			dist[u][v] = std::min(dist[u][v], w);
			dist[v][u] = std::min(dist[v][u], w);
			deg[u]++;
			deg[v]++;
			sum += w;
		}

		floyd_warshall();

		nr_odd = 0;
		for (int i = 1; i <= N; ++i)
			if (deg[i] % 2)
				odd[nr_odd++] = i;

		sum += search((1 << nr_odd) - 1);
		printf("%d\n", sum);
	}

	return 0;
}