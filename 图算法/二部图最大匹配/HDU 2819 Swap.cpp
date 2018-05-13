// HDU 2819 Swap
// �������ͼ�����Ҳ����Ͼ�Ϊ{1, 2, ..., n}
// ��������ľ����е�i�е�j��Ϊ1����ô����ӱ�(i, j)
// ��ʾ�����ڵ�j�е�Ԫ���ܵ��˵�i��

// ���Ȿ���ǵ�λ���󾭹������о���任
// ���о�����ȫ���У����ö���ͼ��ʾ��һһӳ��(���ƥ��)����ʾ
// �����ҵ����ƥ����ܹ������

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
	// �޽�
	if (ans != N) {
		cout << -1 << endl;
		return;
	}
	// ��һ��ͳ�ƽ�������
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
	// �ڶ��������������
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
