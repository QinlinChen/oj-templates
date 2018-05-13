// HDU 4474 Yet Another Multiple Problem
// BFS + ºÙ÷¶

#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

#define MAXN 10005
#define NIL -1

int N, M;
bool is_available[10];
int pre[MAXN], digit[MAXN];

void print(int node) {
	if (node == NIL)
		return;
	print(pre[node]);
	printf("%d", digit[node]);
}

void bfs() {
	memset(pre, NIL, sizeof(pre));
	memset(digit, NIL, sizeof(digit));
	queue<int> Q;

	for (int d = 1; d < 10; d++)
		if (is_available[d]) {
			int node = d % N;
			if (node == 0) {
				printf("%d", d);
				return;
			}
			digit[node] = d;
			Q.push(node);
		}

	while (!Q.empty()) {
		int node = Q.front();
		Q.pop();

		for (int d = 0; d < 10; d++)
			if (is_available[d]) {
				int next_node = (node * 10 + d) % N;
				if (digit[next_node] == NIL) {
					pre[next_node] = node;
					digit[next_node] = d;
					Q.push(next_node);
				}
				if (next_node == 0) {
					print(next_node);
					return;
				}
			}
	}
	printf("-1");
}

int main() {
	int cases = 0;
	while (scanf("%d%d", &N, &M) != EOF) {
		memset(is_available, true, sizeof(is_available));
		for (int i = 0; i < M; i++) {
			int x;
			scanf("%d", &x);
			is_available[x] = false;
		}

		printf("Case %d: ", ++cases);
		bfs();
		printf("\n");
	}
	return 0;
}