#include <cstdio>
using namespace std;

#define MAXN 100005
typedef long long LL;

int N, A[MAXN], map[MAXN];

int complement(int n) {
	int ret = 0;
	while (ret < n)
		ret = (ret << 1) + 1;
	return ret - n;
}

void build_map() {
	for (int i = 0; i <= N; ++i)
		map[i] = 0;
	for (int i = N; i >= 0; --i)
		if (!map[i]) {
			int c = complement(i);
			map[i] = c;
			map[c] = i;
		}
}

LL integrating_degree() {
	LL sum = 0;
	for (int i = 0; i <= N; ++i)
		sum += i ^ map[i];
	return sum;
}

int main() {
	while (scanf("%d", &N) != EOF) {
		for (int i = 0; i <= N; ++i)
			scanf("%d", &A[i]);

		build_map();
		printf("%lld\n", integrating_degree());
		for (int i = 0; i <= N; ++i) {
			if (i != 0)
				printf(" ");
			printf("%d", map[A[i]]);
		}
		printf("\n");
	}
}