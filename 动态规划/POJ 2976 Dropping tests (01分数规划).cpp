// POJ 2976 Dropping tests 
// 01分数规划

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 1000
#define EPS 1e-5

int N, K;
int A[MAXN], B[MAXN];
double C[MAXN];

double iterate(double R) {
	for (int i = 0; i < N; i++)
		C[i] = A[i] - R * B[i];
	sort(C, C + N);

	double ret = 0.0;
	for (int i = K; i < N; i++)
		ret += C[i];
	return ret;
}

int main() {
	while (scanf("%d %d", &N, &K) != EOF) {
		if (N == 0 && K == 0)
			break;
		for (int i = 0; i < N; i++)
			scanf("%d", &A[i]);
		for (int i = 0; i < N; i++)
			scanf("%d", &B[i]);

		double l = 0.0, r = 1.0, mid;
		while (r - l > EPS) {
			mid = (r + l) / 2;
			if (iterate(mid) > 0)
				l = mid;
			else
				r = mid;
		}
		printf("%d\n", (int)(100 * mid + 0.5));
	}
	return 0;
}