//poj1837 Balance
//本题要点
//如何转化为DP
//方法数是“最优解”，力矩和是“背包的容量”

#include <iostream>
#include <cstring>
#define FOR(I,A,B) for(int I=A;I<=B;++I)
using namespace std;

int dp[21][15001];
int C[21];
int G[21];
int g, c;

int main()
{
	while (cin >> c >> g) {
		memset(dp, 0, sizeof(dp));
		dp[0][7500] = 1;
		FOR(i, 1, c)
			scanf("%d", C + i);
		FOR(i, 1, g)
			scanf("%d", G + i);
		FOR(i, 1, g)
			FOR(m, 1, 15000)
				if (dp[i - 1][m])
					FOR(k, 1, c)
						dp[i][m + C[k] * G[i]] += dp[i - 1][m];
		cout << dp[g][7500] << endl;

	}
}