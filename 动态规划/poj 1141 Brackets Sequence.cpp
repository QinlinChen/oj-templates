#include <iostream>  
#include <cstdio>  
#include <cstring>  
using namespace std;
#define MAXN 200  
char str[MAXN];
int dp[MAXN][MAXN], pos[MAXN][MAXN];

void print(int i, int j) {
	if (i > j)
		return;
	if (i == j) {
		if (str[i] == '(' || str[j] == ')')
			printf("()");
		else
			printf("[]");
	}
	else if (pos[i][j] == -1) {
		printf("%c", str[i]);
		print(i + 1, j - 1);
		printf("%c", str[j]);
	}
	else {
		print(i, pos[i][j]);
		print(pos[i][j] + 1, j);
	}
}

bool match(int i, int j)
{
	if (str[i] == '(' && str[j] == ')')
		return true;
	if (str[i] == '[' && str[j] == ']')
		return true;
	return false;
}

int main() 
{
	while (gets(str) != NULL) {
		memset(dp, 0, sizeof(dp));
		int length = strlen(str);
		for (int i = 0; i < length; i++)
			dp[i][i] = 1;

		for (int len = 1; len < length; len++) {
			for (int lo = 0; lo + len < length; lo++) {
				int hi = lo + len;
				dp[lo][hi] = 0x7fffffff;
				if (match(lo, hi)) {
					//如果当前位置匹配，那么pos置-1  
					dp[lo][hi] = dp[lo + 1][hi - 1];
					pos[lo][hi] = -1;
				}
				for (int mid = lo; mid < hi; mid++) {
					int temp = dp[lo][mid] + dp[mid + 1][hi];
					if (dp[lo][hi] > temp) {
						//如果存在更优分解，那么选择更优分解  
						dp[lo][hi] = temp;
						pos[lo][hi] = mid;
					}
				}
			}
		}
		print(0, length - 1);
		printf("\n");
	}

	return 0;
}