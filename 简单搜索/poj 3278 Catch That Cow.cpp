//poj3278 Catch That Cow
//本题要点
//bfs
//注意cx > K 和 cx < 0 时的nx的选择

#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int N, K;
bool marked[200000];
int d[200000];

void bfs()
{
	int cx = N;
	queue<int> q;
	q.push(cx);
	marked[cx] = true;
	d[cx] = 0;
	while (!q.empty()) {
		cx = q.front();
		q.pop();
		if (cx == K)
			return;
		vector<int> nx;
		if (cx > K)			nx.push_back(cx - 1);
		else if (cx <= 0)	nx.push_back(cx + 1);
		else {
			nx.push_back(cx + 1);
			nx.push_back(cx - 1);
			nx.push_back(cx * 2);
		}
			
		for (int i = 0; i < nx.size(); ++i) {
			if (!marked[nx[i]]) {
				q.push(nx[i]);
				marked[nx[i]] = true;
				d[nx[i]] = d[cx] + 1;
			}
		}
	}
}

int main()
{
	while (cin >> N >> K) {
		memset(marked, 0, sizeof(marked));
		bfs();
		cout << d[K] << endl;
	}
}