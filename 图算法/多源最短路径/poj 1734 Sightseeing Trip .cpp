// poj 1734 Sightseeing Trip 
// 求一个有向图的最小环
// 因为每个环中有一个最大的结点
// 所以用FloydWarshall算法
// 在每次循环开始前，任何点的当前最短路径只包括{1,2,...k}时，
// 遍历任意两个结点看是否能与k+1结点成环，这个环中k+1为最大的结点。
// 有的话，就记录下来。

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 105
#define INF 10000000
#define NIL -1
int N, M;
int W[MAXN][MAXN], D[MAXN][MAXN], PI[MAXN][MAXN];
int mincycle, ctr;
int path[MAXN];

void initialize()
{
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			W[i][j] = INF;
	memset(PI, 0xff, sizeof(PI));
	for (int i = 1; i <= N; ++i)
		W[i][i] = 0;
	int u, v, w;
	for (int i = 1; i <= M; ++i) {
		scanf("%d %d %d", &u, &v, &w);
		if (w < W[u][v]) {
			W[u][v] = W[v][u] = w;
			PI[u][v] = u;
			PI[v][u] = v;
		}		
	}
}

void FloydWarshall()
{
	memcpy(D, W, sizeof(W));
	mincycle = INF;
	for (int k = 1; k <= N; ++k) {
		for (int i = 1; i < k; ++i)
			for (int j = i + 1; j < k; ++j) {
				int cycle = D[i][j] + W[j][k] + W[k][i];
				if (mincycle > cycle) {
					mincycle = cycle;
					ctr = 0;
					path[ctr++] = k;
					int p = i;
					while (p != j) {
						path[ctr++] = p;
						p = PI[j][p];
					}
					path[ctr++] = j;
				}
			}

		for (int i = 1; i <= N; ++i)
			for (int j = 1; j <= N; ++j)
				if (D[i][j] > D[i][k] + D[k][j]) {
					D[i][j] = D[i][k] + D[k][j];
					PI[i][j] = PI[k][j];
				}
	}
}

void output()
{
	cout << path[0];
	for (int i = 1; i < ctr; ++i)
		cout << " " << path[i];
	cout << endl;
}

int main()
{
	while (cin >> N) {
		if (N < 0)
			break;
		cin >> M;
		initialize();
		FloydWarshall(); 
		if (mincycle == INF)
			cout << "No solution.\n";
		else
			output();
	}
}


/*
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 105
#define INF 10000000

int D[MAXN][MAXN], W[MAXN][MAXN], PI[MAXN][MAXN];
int path[MAXN];
int N, M, ctr, mincycle;

void Floyd()
{
	int i, j, k, p, tmp;
	mincycle = INF;
	for (k = 1; k <= N; k++) {
		for (i = 1; i<k; i++)
			for (j = i + 1; j<k; j++)
			{
				tmp = D[i][j] + W[i][k] + W[k][j];
				if (tmp<mincycle) //找到更优解
				{
					mincycle = tmp;
					ctr = 0;
					p = j;
					while (p != i) //逆向寻找前驱结点直到找到最前面的i,i->…->j
					{
						path[ctr++] = p;
						p = PI[i][p];//fa[i][j]保存的不是k,而是fa[k][j].
					}
					path[ctr++] = i;
					path[ctr++] = k;
				}
			}
		for (i = 1; i <= N; i++)
			for (j = 1; j <= N; j++)
			{
				tmp = D[i][k] + D[k][j];
				if (D[i][j]>tmp)
				{
					D[i][j] = tmp;
					PI[i][j] = PI[k][j];
				}
			}
	}
}

int main()
{
	int i, j, u, v, w;
	while (scanf("%d%d", &N, &M) != EOF)
	{
		for (i = 1; i <= N; i++)
			for (j = 1; j <= N; j++)
			{
				W[i][j] = INF;
				D[i][j] = INF;
				PI[i][j] = i;
			}
		while (M--)
		{
			scanf("%d%d%d", &u, &v, &w);
			w = min(W[u][v], w);          //处理重边
			W[u][v] = W[v][u] = D[u][v] = D[v][u] = w;
		}
		Floyd();
		if (mincycle == INF)
			printf("No solution.\n");
		else
		{
			printf("%d", path[0]);
			for (i = 1; i<ctr; i++)
				printf(" %d", path[i]);
			printf("\n");
		}
	}
	return 0;
}
*/