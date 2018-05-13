//用匈牙利算法求二部图的最大匹配

#include <iostream>
#include <cstdio>
#include <cstring>
#include <list>
#include <assert.h>
using namespace std;

#define MAXN 65
#define MAXY 100005

int N, students;
list<int> adj[MAXN];
int match[MAXY];
bool marked[MAXY], has_match[MAXY];

void input()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		adj[i].clear();
	int X, Y;
	for (int u = 1; u <= N; ++u) {
		scanf("%d %d", &X, &Y);
		for (int v = X; v <= Y; ++v)
			adj[u].push_back(v);
	}
}

bool dfs(int u)
{
	for (list<int>::iterator iter = adj[u].begin();
		iter != adj[u].end(); ++iter) {
		int v = *iter;
		if (!marked[v]) {
			marked[v] = true;
			if (match[v] == -1 || dfs(match[v])) {
				match[v] = u;
				has_match[u] = true;		// 这行是本题需要
				return true;
			}
		}
	}
	return false;
}

void solve()
{
	// 匈牙利算法开始
	students = 0;
	memset(match, 0xff, sizeof(match));
	memset(has_match, 0, sizeof(has_match)); // 这行是本题需要
	for (int i = N; i >= 1; --i) {
		memset(marked, 0, sizeof(marked));
		if (dfs(i))
			students++;
	}
	// 匈牙利算法结束
	
	cout << students << endl;
	for (int i = 1; i <= N; ++i) 
		if (has_match[i]) {
			assert(students > 0);
			if (--students == 0)
				cout << i << endl;
			else
				cout << i << " ";
		}
}

int main()
{
	int cases;
	scanf("%d", &cases);
	for (int i = 1; i <= cases; ++i) {
		input();
		solve();
	}
}