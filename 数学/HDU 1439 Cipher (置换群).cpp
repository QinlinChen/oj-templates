// HDU 1439 Cipher
// 置换群
// 考虑每个位置上的字符置换mod[i]次后会恢复原位
// 置换K次等价于置换K % mod[i]次

#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

#define MAXN 205

int N, K;
char str[MAXN], encoded_str[MAXN];
int key[MAXN];
int mod[MAXN];

void initialize()
{
	for (int i = 1; i <= N; ++i)
		scanf("%d", &key[i]);
	for (int i = 1; i <= N; ++i) {
		int count = 1, next = key[i];
		while (next != i) {
			next = key[next];
			count++;
		}
		mod[i] = count;
	}
}

void encode()
{
	for (int i = 1; i <= N; ++i) {
		int j = K % mod[i], next = i;
		while (j-- > 0) {
			next = key[next];
		}
		encoded_str[next] = str[i];
	}
}

int main()
{
	while (scanf("%d", &N) != EOF && N) {
		initialize();
		while (scanf("%d", &K) != EOF && K) {
			fgets(str, MAXN, stdin);
			int len = strlen(str) - 1;
			for (int i = len; i <= N; ++i)
				str[i] = ' ';
			encode();
			for (int i = 1; i <= N; ++i)
				putchar(encoded_str[i]);
			putchar('\n');
		}
		putchar('\n');
	}
}