//poj2349 Arctic Network
//要证明在MST中删除S-1个最大边能得到要求的结果
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <climits>
#include <algorithm>
using namespace std;

#define MAXSIZE 501
#define INF 0x7fffffff

int S, P;
int X[MAXSIZE], Y[MAXSIZE];
double W[MAXSIZE][MAXSIZE];
double key[MAXSIZE];
bool visited[MAXSIZE];

double calcDis(int a, int b)
{
	int dx = X[a] - X[b], dy = Y[a] - Y[b];
	return sqrt((double)(dx * dx + dy * dy));
}

void initialize()
{
	cin >> S >> P;
	for (int i = 0; i < P; ++i)
		scanf("%d %d", &X[i], &Y[i]);
	for (int i = 0; i < P; ++i) {
		W[i][i] = 0.0;
		for (int j = i + 1; j < P; ++j)
			W[i][j] = W[j][i] = calcDis(i, j);
	}
	for (int i = 0; i < P; ++i)
		key[i] = INF;
	memset(visited, 0, sizeof(visited));
}

double primMST()
{
	initialize();
	key[0] = 0;
	for (int ctr = 0; ctr < P; ++ctr) {
		double min = INF;
		int u = -1;
		for (int i = 0; i < P; ++i)
			if (!visited[i] && key[i] < min) {
				min = key[i];
				u = i;
			}
		visited[u] = true;
		for (int v = 0; v < P; ++v)
			if (!visited[v] && W[u][v] < key[v])
				key[v] = W[u][v];
	}
	sort(key, key + P);
	return key[P - S];
}

int main()
{
	int N;
	cin >> N;
	for (int i = 0; i < N; ++i)
		printf("%.2lf\n", primMST());
}