// FOJ 2214 Knapsack problem
// 01背包

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define INF 0x3f3f3f3f3f3f3f3f
#define MAXN 510
#define MAXDP 5010
typedef long long LL;

int n, B;
int W[MAXN], V[MAXN];
LL dp[MAXDP];

void zeroOneKP() {
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = MAXDP; j >= V[i]; --j) {
			dp[j] = std::min(dp[j], dp[j - V[i]] + W[i]);
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for (int cases = 1; cases <= T; ++cases) {
		scanf("%d %d", &n, &B);
		for (int i = 1; i <= n; ++i)
			scanf("%d %d", &W[i], &V[i]);
		zeroOneKP();
		
		
		for (int i = MAXDP - 1; i >= 0; --i) {
			if (dp[i] <= B) {
				printf("%d\n", i);
				break;
			}
		}	
	}
	return 0;
}