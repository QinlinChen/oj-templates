// hdu 1712 ACboy needs your help
// 分组背包问题

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX 105

int N, M;
int A[MAX][MAX];
int dp[MAX];

int group_backpack()
{
	// 分组背包
	memset(dp, 0, sizeof(dp));
	for (int g = 1; g <= N; ++g)
		for (int v = M; v >= 1; --v)
			for (int k = 1; k <= v; ++k)
				dp[v] = std::max(dp[v], dp[v - k] + A[g][k]);
	return dp[M];
}

int main()
{
	while (scanf("%d %d", &N, &M) != EOF) {
		if (N == 0 && M == 0)
			break;
		for (int i = 1; i <= N; ++i)
			for (int j = 1; j <= M; ++j)
				scanf("%d", &A[i][j]);
		printf("%d\n", group_backpack());
	}
}