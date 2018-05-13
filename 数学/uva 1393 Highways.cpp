// uva 1393 Highways

// ����һ������{1...m}X{1...n}(�ѿ�����)
// �������ȼ�������(1,1)������{2...m}X{2...n}�������������в��غϵ��ߵĸ�������������dp[m-1][n-1]�С�
// dp[i][j]���±���ʵ��ʾ����������߳���
// dp[m-1][n-1]�Ľ�����ʽ��, dp[m-1][n-1]=\sum_{(p,q)\in{2...m}X{2...n}}(gcd(p-1, q-1)==1)
// �����ǵݹ�����㣺��{2...m}X{2...n}���{2...m}X{2...n-1}��{2...m-1}X{2...n}���(m,n)���ص��Ĳ�����{2...m-1}X{2...n-1}
// �����ݹ�ʽ�ͳ���dp[m-1][n-1] = dp[m-2][n-1] + dp[m-1][n-2] - dp[m-2][n-2] + (gcd(m-1 ,n-1) == 1)

// Ȼ�������{1...m}X{1...n}����֮���������������в��غϵ��ߵĸ������Ᵽ����ans[m-1][n-1]�С�
// ans[i][j]���±�Ҳ��ʾ����������߳���
// ��Ҳ�ǵݹ����ģ���{1...m}X{1...n}���{2...m}X{1...n}��{1...m}X{2...n}�͵�(1,1)���ص��Ĳ�����{2...m}X{2...n}
// ����С������ߵ������ܵݹ�ؼ��㣬�ɵ�(1,1)�������߾���dp[m-1][n-1]���������ظ����ظ��Ĳ��־���dp[(m-1)>>1][(n-1)>>1]
// ���Եݹ�ʽ���� ans[m-1][n-1] = ans[m-2][n-1] + ans[m-1][n-2] - ans[m-2][n-2] + dp[m-1][n-1] - dp[(m-1)>>1][(n-1)>>1]

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