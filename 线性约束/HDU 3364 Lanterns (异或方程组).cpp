#include<iostream>  
#include<algorithm>  
#include<cstdio>  
#include<cstring>  
#include<cmath>  
using namespace std;
const int MAXN = 55;
const int INF = 0xfffff0;

int Equ, Var;
int A[MAXN][MAXN], B[MAXN][MAXN];
int X[MAXN];
bool FreeX[MAXN];
int FreeNum;

int GCD(int a, int b) { return (b == 0 ? a : GCD(b, a % b)); }
int LCM(int a, int b) { return a / GCD(a, b) * b; }

int Gauss()
{
	int i, j, k;
	int MaxRow;
	int col = 0;
	int Lcm;
	int ta, tb;
	int temp;
	int FreeXNum;
	int FreeIndex;

	for (i = 0; i < Var; ++i) {
		X[i] = 0;
		FreeX[i] = true;
	}

	for (k = 0; k < Equ && col < Var; ++k, ++col) {
		MaxRow = k;
		for (i = k + 1; i < Equ; ++i)
			if (abs(A[i][col]) > abs(A[MaxRow][col]))
				MaxRow = i;
		
		if (MaxRow != k)
			for (j = k; j < Var + 1; ++j)
				swap(A[k][j], A[MaxRow][j]);
		
		if (A[k][col] == 0) {
			k--;
			continue;
		}

		for (i = k + 1; i < Equ; ++i) 
			if (A[i][col]) {
				Lcm = LCM(abs(A[i][col]), abs(A[k][col]));
				ta = Lcm / abs(A[i][col]);
				tb = Lcm / abs(A[k][col]);
				if (A[i][col] * A[k][col] < 0)
					tb = -tb;
				for (j = col; j < Var + 1; ++j)
					A[i][j] = (A[i][j] * ta % 2 - A[k][j] * tb % 2 + 2) % 2;
			}		
	}

	for (i = k; i < Equ; ++i)
		if (A[i][col])
			return -1;

	if (k < Var)
		return Var - k;
	return 0;
}


int main()
{
	int T, t, d, kase = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &Equ, &Var);
		memset(A, 0, sizeof(A));
		memset(B, 0, sizeof(B));
		memset(X, 0, sizeof(X));

		for (int i = 0; i < Var; ++i) {
			scanf("%d", &t);
			while (t--) {
				scanf("%d", &d);
				B[d - 1][i] = 1;
			}
		}
		printf("Case %d:\n", ++kase);

		scanf("%d", &t);
		while (t--) {
			memcpy(A, B, sizeof(B));
			for (int i = 0; i < Equ; ++i)
				scanf("%d", &A[i][Var]);
			int Ans = Gauss();
			if (Ans == -1)
				printf("0\n");
			else
				printf("%I64d\n", 1LL << (Ans));
		}
	}

	return 0;
}