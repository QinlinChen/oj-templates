// uva 1393 Highways

// 对于一个点阵{1...m}X{1...n}(笛卡尔积)
// 我们首先计算从起点(1,1)到点阵{2...m}X{2...n}所能引出的所有不重合的线的个数，并保存在dp[m-1][n-1]中。
// dp[i][j]的下标其实表示点阵的两个边长。
// dp[m-1][n-1]的解析公式是, dp[m-1][n-1]=\sum_{(p,q)\in{2...m}X{2...n}}(gcd(p-1, q-1)==1)
// 但我们递归地来算：把{2...m}X{2...n}拆成{2...m}X{2...n-1}、{2...m-1}X{2...n}与点(m,n)，重叠的部分是{2...m-1}X{2...n-1}
// 这样递归式就成了dp[m-1][n-1] = dp[m-2][n-1] + dp[m-1][n-2] - dp[m-2][n-2] + (gcd(m-1 ,n-1) == 1)

// 然后算点阵{1...m}X{1...n}两两之间所能引出的所有不重合的线的个数，这保存在ans[m-1][n-1]中。
// ans[i][j]的下标也表示点阵的两个边长。
// 这也是递归计算的：把{1...m}X{1...n}拆成{2...m}X{1...n}、{1...m}X{2...n}和点(1,1)，重叠的部分是{2...m}X{2...n}
// 三个小点阵的线的条数能递归地计算，由点(1,1)引出的线就是dp[m-1][n-1]，但这有重复，重复的部分就是dp[(m-1)>>1][(n-1)>>1]
// 所以递归式就是 ans[m-1][n-1] = ans[m-2][n-1] + ans[m-1][n-2] - ans[m-2][n-2] + dp[m-1][n-1] - dp[(m-1)>>1][(n-1)>>1]

#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <algorithm>  
typedef long long LL;
using namespace std;
#define MAXN 310

int n, m;
LL dp[MAXN][MAXN], ans[MAXN][MAXN];

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

void init() {
	memset(dp, 0, sizeof(dp));
	memset(ans, 0, sizeof(ans));

	for (int i = 1; i <= 300; i++)
		for (int j = 1; j <= 300; j++)
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + (gcd(i, j) == 1);

	for (int i = 1; i <= 300; i++)
		for (int j = 1; j <= 300; j++)
			ans[i][j] = ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1] + dp[i][j] - dp[i >> 1][j >> 1];
}

int main() {
	init();
	while (scanf("%d%d", &n, &m) != EOF && n + m) {
		printf("%lld\n", ans[n - 1][m - 1] * 2);
	}
	return 0;
}