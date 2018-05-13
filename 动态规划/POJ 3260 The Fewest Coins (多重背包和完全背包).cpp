// POJ 3260 The Fewest Coins
// 多重背包和完全背包问题
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 105
#define MAXV 125
#define MAXT 10005
#define MAXSIZE MAXV*MAXV+MAXT
#define INF 0x3f3f3f3f

int N, T;
int V[MAXN], C[MAXN];
int dp_kj[MAXSIZE], dp_sk[MAXSIZE];

int main() {
	while (scanf("%d %d", &N, &T) != EOF) {
		int lim = 0;
		for (int i = 1; i <= N; ++i) {
			scanf("%d", &V[i]);
			lim = std::max(lim, V[i]);
		}
		lim = (lim * lim) + T;
		for (int i = 1; i <= N; ++i)
			scanf("%d", &C[i]);

		// multi_kp
		memset(dp_kj, 0x3f, sizeof(dp_kj));
		dp_kj[0] = 0;
		for (int i = 1; i <= N; ++i) {
			if (V[i] * C[i] >= lim) {
				for (int j = V[i]; j <= lim; ++j)
					dp_kj[j] = std::min(dp_kj[j], dp_kj[j - V[i]] + 1);
			}
			else {
				int k = 1;
				while (k < C[i]) {
					for (int j = lim; j >= k * V[i]; --j)
						dp_kj[j] = std::min(dp_kj[j], dp_kj[j - k * V[i]] + k);
					C[i] -= k;
					k <<= 1;
				}
				for (int j = lim; j >= C[i] * V[i]; --j)
					dp_kj[j] = std::min(dp_kj[j], dp_kj[j - C[i] * V[i]] + C[i]);
			}
		}
		
		// complete_kp
		memset(dp_sk, 0x3f, sizeof(dp_sk));
		dp_sk[0] = 0;
		for (int i = 1; i <= N; ++i) 
			for (int j = V[i]; j <= lim; ++j)
				dp_sk[j] = std::min(dp_sk[j], dp_sk[j - V[i]] + 1);
		
		// output
		int ans = INF;
		for (int i = T; i <= lim; i++)
			ans = std::min(ans, dp_kj[i] + dp_sk[i - T]);
		if (ans == INF)
			ans = -1; 
		printf("%d\n", ans);
	}
}