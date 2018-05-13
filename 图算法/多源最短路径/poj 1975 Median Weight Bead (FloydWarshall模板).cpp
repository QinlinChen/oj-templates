// poj 1975 Median Weight Bead
// 求一个传递闭包

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 105
#define INF 0x3f3f3f3f
int N, M;
int W[MAXN][MAXN];
int D[MAXN][MAXN];

void initialize()
{
	memset(W, 0x3f, sizeof(W));
	for (int i = 1; i <= N; ++i)
		W[i][i] = 0;
	int u, v;
	for (int i = 1; i <= M; ++i) {
		scanf("%d %d", &u, &v);
		W[u][v] = 1;
	}
}

void FloydWarshall()
{
	memcpy(D, W, sizeof(W));
	for (int k = 1; k <= N; ++k)
		for (int i = 1; i <= N; ++i)
			for (int j = 1; j <= N; ++j)
				if (D[i][j] > D[i][k] + D[k][j])
					D[i][j] = D[i][k] + D[k][j];
}

int count()
{
	int ctr = 0;
	for (int i = 1; i <= N; ++i) {
		int less = 0, greater = 0;
		for(int j = 1; j <= N; ++j)
			if (i != j) {
				if (D[i][j] < INF)
					less++;
				if (D[j][i] < INF)
					greater++;
			}
		if (greater > N / 2 || less > N / 2)
			ctr++;
	}
	return ctr;
}

int main()
{
	int T;
	cin >> T;
	for (int i = 1; i <= T; ++i) {
		cin >> N >> M;
		initialize();
		FloydWarshall();
		cout << count() << endl;
	}
}