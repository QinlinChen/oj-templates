// HDU 3976 Electric resistance
// 高斯消元解电路方程

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <assert.h>
using namespace std;

#define MAXN 55

int N, M;
double A[MAXN][MAXN];
double B[MAXN], X[MAXN];
int pi[MAXN];

void swapRows(int r1, int r2)
{
	double temp_row[MAXN];
	for (int c = 0; c < N; ++c)
		temp_row[c] = A[r1][c];
	for (int c = 0; c < N; ++c)
		A[r1][c] = A[r2][c];
	for (int c = 0; c < N; ++c)
		A[r2][c] = temp_row[c];
}

void swapPi(int i, int j)
{
	double temp = pi[i];
	pi[i] = pi[j];
	pi[j] = temp;
}

void LUP() {
	for (int i = 0; i < N; ++i)
		pi[i] = i;

	for (int k = 0; k < N; ++k) {
		double pivot = 0, element;
		int minRow;
		for (int i = k; i < N; ++i) {
			element = A[i][k];
			if (fabs(element) > pivot) {
				pivot = element;
				minRow = i;
			}
		}
		assert(pivot != 0);
		if (k != minRow) {
			swapRows(k, minRow);
			swapPi(k, minRow);
		}
		for (int i = k + 1; i < N; ++i) {
			A[i][k] /= A[k][k];
			for (int j = k + 1; j < N; ++j)
				A[i][j] -= A[i][k] * A[k][j];
		}
	}

	double y[MAXN];
	for (int i = 0; i < N; ++i) {
		y[i] = B[pi[i]];
		for (int j = 0; j < i; ++j)
			y[i] -= A[i][j] * y[j];
	}
	for (int i = N - 1; i >= 0; --i) {
		X[i] = y[i];
		for (int j = i + 1; j < N; ++j)
			X[i] -= A[i][j] * X[j];
		X[i] /= A[i][i];
	}
}

void initialize()
{
	scanf("%d %d", &N, &M);
	int a, b;
	double c;
	memset(A, 0, sizeof(A));
	for (int i = 1; i <= M; ++i) {
		scanf("%d %d %lf", &a, &b, &c);
		a--;
		b--;
		c = 1.0 / c;
		A[a][a] += c;
		A[b][b] += c;
		A[a][b] -= c;
		A[b][a] -= c;
	}
	for (int i = 0; i < N; ++i)
		for (int j = 1; j < N; ++j)
			A[i][j - 1] = A[i][j];
	
	memset(B, 0, sizeof(B));
	B[0] = 1;
	N--;
}

int main()
{
	int cases;
	scanf("%d", &cases);
	for (int i = 1; i <= cases; ++i) {
		initialize();
		LUP();
		printf("Case #%d: %.2lf\n", i, -X[N - 1]);
	}
}
