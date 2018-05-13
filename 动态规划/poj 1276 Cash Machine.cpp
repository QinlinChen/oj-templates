//poj1276 Cash Machine
//本题要点
//对多重背包问题的二进制优化转化为01背包问题

//01背包问题的优化模板为：
//for i=1..N 
//	for v=V..0 
//		f[v]=max{f[v],f[v-c[i]]+w[i]}; 

//完全背包问题的优化模板为：
//for i=1..N
//	for v=0..V 
//		f[v]=max{f[v],f[v-c[i]]+w[i]}

#include <iostream>
#include <cstdio>
#define MAX(x, y) ((x)>(y)?(x):(y))
using namespace std;

int cash, N;
int biop[1000];	//二进制优化

int main()
{
	while (cin >> cash >> N) {
		int *dp = new int[cash + 1];
		for (int i = 0; i <= cash; ++i)
			dp[i] = 0;
		int len = 0, n, D;
		for (int i = 1; i<= N; i++) {
			scanf("%d %d", &n, &D);
			for (int k = 1; k <= n; k <<= 1) {
				biop[len++] = k * D;
				n -= k;
			}
			if (n > 0) {
				biop[len++] = n * D;
			}
		}

		for (int i = 0; i < len; ++i)
			for (int v = cash; v >= biop[i]; --v)
				dp[v] = MAX(dp[v], dp[v - biop[i]] + biop[i]);


		cout << dp[cash] << endl;

		delete[] dp;
	}
}