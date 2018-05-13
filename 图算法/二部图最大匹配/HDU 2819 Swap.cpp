// HDU 2819 Swap
// 构造二部图，左部右部集合均为{1, 2, ..., n}
// 如果给定的矩阵中第i行第j列为1，那么，添加边(i, j)
// 表示本该在第j行的元素跑到了第i行

// 该题本质是单位矩阵经过了排列矩阵变换
// 排列矩阵是全排列，能用二部图表示的一一映射(最大匹配)来表示
// 所以找到最大匹配就能构造答案了

#include <iostream>
#include <cstdio>
#include <cstring>
#include <list>
#include <assert.h>
using namespace std;

#define MAXN 105

int N;
list<int> adj[MAXN];
bool marked[MAXN];
int match[MAXN];

void input()
{
	for (int i = 1; i <= N; ++i)
		adj[i].clear();
	int data;
	for(int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j) {
			scanf("%d", &data);
			if (data)
				adj[i].push_back(j);
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
				return true;
			}
		}
	}
	return false;
}

void solve()
{
	int ans = 0;
	memset(match, 0xff, sizeof(match));
	for (int i = N; i >= 1; --i) {
		memset(marked, 0, sizeof(marked));
		if (dfs(i))
			ans++;
	}
	// 无解
	if (ans != N) {
		cout << -1 << endl;
		return;
	}
	// 第一遍统计交换次数
	int temp[MAXN];
	int ctr = 0;
	memcpy(temp, match, sizeof(match));
	for (int right = 1; right <= N; ++right) {
		int left = temp[right];
		if (left != right) {
			int k;
			for (k = right; k <= N; ++k)
				if (temp[k] == right)
					break;
			assert(k != right);
			ctr++;
			temp[k] = left;
			temp[right] = right;
		}
	}
	cout << ctr << endl;
	// 第二遍输出交换方法
	for (int right = 1; right <= N; ++right) {
		int left = match[right];
		if (left != right) {
			int k;
			for (k = right; k <= N; ++k)
				if (match[k] == right)
					break;
			assert(k != right);
			printf("R %d %d\n", right, left);
			match[k] = left;
			match[right] = right;
		}
	}
}

int main()
{
	while (cin >> N) {
		input();
		solve();
	}
}
