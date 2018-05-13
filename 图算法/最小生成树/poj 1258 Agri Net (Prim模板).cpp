//poj1256 Agri Net
//PrimMST

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXSIZE 101
#define INF 0x7fffffff
int N;
int W[MAXSIZE][MAXSIZE];
int dist[MAXSIZE];
bool visited[MAXSIZE];

void initialize()
{
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			scanf("%d", &W[i][j]);
	for (int i = 0; i < N; ++i)
		dist[i] = INF;
	memset(visited, 0, sizeof(visited));
}

int PrimMST()
{
	dist[0] = 0;
	int shortest = 0;

	for (int ctr = 0; ctr < N; ++ctr) {
		int min = INF, u = -1;
		for (int i = 0; i < N; ++i)
			if (!visited[i] && dist[i] < min) {
				min = dist[i];
				u = i;
			}
		visited[u] = true;
		shortest += dist[u];

		for (int v = 0; v < N; ++v)
			if (!visited[v] && W[u][v] < dist[v])
				dist[v] = W[u][v];
	}
	return shortest;
}

int main()
{
	while (cin >> N) {
		initialize();
		cout << PrimMST() << endl;
	}
	return 0;
}