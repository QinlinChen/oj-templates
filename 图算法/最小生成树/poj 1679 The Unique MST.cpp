//poj1679 The Unique MST
//判断是否有唯一的MST
//可以尝试算出MST，然后添加不在树中的边，形成新的环。
//查看是否可以删去环上的一边得到新的MST。
//或者采用次小生成树。

#include <iostream>
#include <cstdio>
using namespace std;

#define MAXSIZE 105
#define INF 0x7fffffff
#define NIL -1;

int N, M;
int W[MAXSIZE][MAXSIZE];
bool hasEdge[MAXSIZE][MAXSIZE];
bool inTree[MAXSIZE][MAXSIZE];
int key[MAXSIZE], pi[MAXSIZE];
bool visited[MAXSIZE];
int totalCost;

void initialize()
{
	cin >> N >> M;
	int u, v, w;
	memset(hasEdge, 0, sizeof(hasEdge));
	memset(inTree, 0, sizeof(inTree));
	for (int i = 1; i <= M; ++i) {
		scanf("%d %d %d", &u, &v, &w);
		W[u][v] = W[v][u] = w;
		hasEdge[u][v] = hasEdge[v][u] = true;
	}
	for (int i = 1; i <= N; ++i)
		key[i] = INF;
	for (int i = 1; i <= N; ++i)
		pi[i] = NIL;
	memset(visited, 0, sizeof(visited));
}

int PrimMST()
{
	initialize();
	key[1] = 0;
	totalCost = 0;

	for (int ctr = 1; ctr <= N; ++ctr) {
		int min = INF, u = -1;
		for (int i = 1; i <= N; ++i)
			if (!visited[i] && key[i] < min) {
				min = key[i];
				u = i;
			}
		visited[u] = true;
		if(u != 1)
			inTree[u][pi[u]] = inTree[pi[u]][u] = true;
		totalCost += key[u];
		for (int v = 1; v <= N; ++v)
			if (hasEdge[u][v] && !visited[v] && W[u][v] < key[v]) {
				key[v] = W[u][v];
				pi[v] = u;
			}
	}
	return totalCost;
}

bool isUnique()
{
	for(int i = 1; i <= N; ++i)
		for(int j = i + 1; j <= N; ++j)
			if (hasEdge[i][j] && !inTree[i][j]) {
				int w = W[i][j];
				for (int v = i; v != 1; v = pi[v])
					if (key[v] >= w)
						return false;
				for (int v = j; v != 1; v = pi[v])
					if (key[v] >= w)
						return false;
			}
	return true;
}

int main()
{
	int cases;
	cin >> cases;
	for (int i = 1; i <= cases; ++i) {
		PrimMST();
		if (isUnique())
			cout << totalCost << endl;
		else
			cout << "Not Unique!" << endl;
	}
}