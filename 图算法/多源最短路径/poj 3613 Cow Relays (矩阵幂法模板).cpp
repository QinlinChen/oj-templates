// poj 3613 Cow Relays
// 核心是求长度为k的多源最短路径
// 类似于用矩阵求多源最短路径，每次矩阵相乘来扩边
// 要注意的是，w[i][i] = infinity，不然扩边的时候会把自环扩进去，就会不变
// k可能很大，要用矩阵连乘来优化
// 这道题由于边远比点少，所以利用map把原先的点集映射到一个更小的点集优化了一下

#include <iostream>
#include <cstdio>
using namespace std;

#define MAXI 1005
#define INF 0x3f3f3f3f

int N, T, S, E, I;
int W[MAXI][MAXI], L[MAXI][MAXI], temp[MAXI][MAXI];
int map[MAXI];

void initialize()
{
	memset(W, 0x3f, sizeof(W));
	memset(map, 0, sizeof(map));
	I = 0;
	int w, u, v;
	for (int i = 1; i <= T; i++) {
		scanf("%d %d %d", &w, &u, &v);
		if (map[u] == 0) 
			map[u] = ++I;
		if (map[v] == 0)
			map[v] = ++I;
		u = map[u];
		v = map[v];
		W[u][v] = W[v][u] = w;
	}
}

void extendShortestPaths(int lhs[MAXI][MAXI], int rhs[MAXI][MAXI])
{
	for(int i = 1; i <= I; ++i)
		for (int j = 1; j <= I; ++j) {
			int min = INF;
			for (int k = 1; k <= I; ++k)
				if (min > lhs[i][k] + rhs[k][j])
					min = lhs[i][k] + rhs[k][j];
			temp[i][j] = min;
		}
	for (int i = 1; i <= I; ++i)
		for (int j = 1; j <= I; ++j)
			lhs[i][j] = temp[i][j];
}

int main()
{
	while (cin >> N >> T >> S >> E) {
		initialize();
		memcpy(L, W, sizeof(W));
		N--;
		while (N) {
			if (N & 0x1)
				extendShortestPaths(L, W);
			extendShortestPaths(W, W);
			N >>= 1;
		}
		cout << L[map[S]][map[E]] << endl;
	}
}