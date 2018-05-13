#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 100005

int N, bin_len, L[MAXN];

int bin_needed() {
	int ans = 0;

	sort(L, L + N);
	for (int i = N - 1; i >= 0; --i) {
		if (L[i]) {
			for (int j = i - 1; j >= 0; --j) {
				if (L[j] && L[i] + L[j] <= bin_len) {
					L[j] = 0;
					break;
				}
			}
			L[i] = 0;
			ans++;
		}
	}
	return ans;
}

int main() {
	int cases;
	scanf("%d", &cases);
	for (int k = 1; k <= cases; ++k) {
		scanf("%d %d", &N, &bin_len);
		for (int i = 0; i < N; ++i)
			scanf("%d", &L[i]);
		if (k != 1)
			printf("\n");
		printf("%d\n", bin_needed());
	}
}