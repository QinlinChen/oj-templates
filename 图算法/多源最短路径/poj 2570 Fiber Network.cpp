// poj 2570 Fiber Network
// 利用位运算来同时求多个重叠图的多源最短路径

#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

#define MAXN 205

int N;
int D[MAXN][MAXN];

void initialize()
{
	int u, v;
	char buf[100];
	memset(D, 0, sizeof(D));
	for (int i = 1; i <= N; ++i)
		D[i][i] = 0xffffffff;
	while (true) {
		scanf("%d %d", &u, &v);
		if (u == 0 && v == 0)
			break;
		scanf("%s", buf);
		for (int i = 0; buf[i] != '\0'; ++i)
			D[u][v] |= (0x1 << (buf[i] - 'a'));
	}
}

void FloydWarshall()
{
	for (int k = 1; k <= N; ++k)
		for (int i = 1; i <= N; ++i)
			for (int j = 1; j <= N; ++j)
				D[i][j] = D[i][j] | (D[i][k] & D[k][j]);
}

void query(int from, int to)
{
	int companys = D[from][to];
	string ret;
	int mask = 0x1;
	for (int i = 0; i < 26; ++i) {
		if (companys & mask) 
			ret.push_back('a' + i);
		mask <<= 1;
	}
	if (ret.empty())
		cout << "-\n";
	else
		cout << ret << endl;
}

int main()
{
	while (cin >> N) {
		if (N == 0)
			break;
		initialize();
		FloydWarshall();
		int a, b;
		while (true) {
			scanf("%d %d", &a, &b);
			if (a == 0 && b == 0)
				break;
			query(a, b);
		}
		cout << endl;
	}

}