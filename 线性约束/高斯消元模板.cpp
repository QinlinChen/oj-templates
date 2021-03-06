#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;

const int MAXN = 50;

int A[MAXN][MAXN];//增广矩阵
int X[MAXN];//解集
bool freeX[MAXN];//标记是否是不确定的变元

inline int gcd(int a, int b)
{
	int t;
	while (b != 0) {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}

inline int lcm(int a, int b) { return a / gcd(a, b)*b; }

// 高斯消元法解方程组(Gauss-Jordan elimination).
// -2表示有浮点数解，但无整数解；-1表示无解；
// 0表示唯一解，大于0表示无穷解，并返回自由变元的个数
// 有equ个方程，var个变元。增广矩阵行数为equ,分别为0到equ-1,列数为var+1,分别为0到var.
int Gauss(int equ, int var)
{
	int i, j, k;
	int maxRow;	// 当前这列绝对值最大的行.
	int col;	
	int ta, tb;
	int LCM;
	int temp;
	int freeVarNum;
	int freeIndex;

	for (int i = 0; i <= var; i++) {
		X[i] = 0;
		freeX[i] = true;
	}

	//转换为阶梯阵.
	col = 0; 
	for (k = 0; k < equ && col < var; k++, col++) { 
	    // 枚举当前处理的行，找到该col列元素绝对值最大的那行与第k行交换(为了在除法时减小误差)
		maxRow = k;
		for (i = k + 1; i < equ; i++)
			if (abs(A[i][col])>abs(A[maxRow][col]))
				maxRow = i;
		// 与第k行交换
		if (maxRow != k)
			for (j = k; j < var + 1; j++) 
				swap(A[k][j], A[maxRow][j]);
		// 如果该col列第k行以下全是0了，则处理当前行的下一列.
		if (A[k][col] == 0) {
			k--;
			continue;
		}
		// 消去行
		for (i = k + 1; i < equ; i++)
			if (A[i][col] != 0) {
				LCM = lcm(abs(A[i][col]), abs(A[k][col]));
				ta = LCM / abs(A[i][col]);
				tb = LCM / abs(A[k][col]);
				if (A[i][col] * A[k][col]<0)
					tb = -tb;	//异号的情况是相加
				for (j = col; j < var + 1; j++)
					A[i][j] = A[i][j] * ta - A[k][j] * tb;
			}
	}

	// 无解的情况: 化简的增广阵中存在(0, 0, ..., a)这样的行(a != 0).
	for (i = k; i < equ; i++)
		if (A[i][col] != 0)
			return -1;

	// 无穷解的情况: 在var * (var + 1)的增广阵中出现(0, 0, ..., 0)这样的行，即说明没有形成严格的上三角阵.
	// 出现的行数即为自由变元的个数.
	if (k < var) {
		// 首先，自由变元有var - k个，即不确定的变元至少有var - k个.
		for (i = k - 1; i >= 0; i--) {
			// 第i行一定不会是(0, 0, ..., 0)的情况，因为这样的行是在第k行到第equ行.
			// 同样，第i行一定不会是(0, 0, ..., a), a != 0的情况，这样的无解的.
			freeVarNum = 0; // 用于判断该行中的不确定的变元的个数，如果超过1个，则无法求解，它们仍然为不确定的变元.
			for (j = 0; j < var; j++)
				if (A[i][j] != 0 && freeX[j])
					freeVarNum++, freeIndex = j;

			if (freeVarNum > 1) 
				continue; // 无法求解出确定的变元, 说明就只有一个不确定的变元free_index，那么可以求解出该变元，且该变元是确定的.
										  
			temp = A[i][var];
			for (j = 0; j < var; j++)
				if (A[i][j] != 0 && j != freeIndex)
					temp -= A[i][j] * X[j];

			X[freeIndex] = temp / A[i][freeIndex]; // 求出该变元.
			freeX[freeIndex] = 0; // 该变元是确定的.
		}
		return var - k; // 自由变元有var - k个.
	}

	// 唯一解的情况: 在var * (var + 1)的增广阵中形成严格的上三角阵计算出Xn-1, Xn-2 ... X0.
	for (i = var - 1; i >= 0; i--) {
		temp = A[i][var];
		for (j = i + 1; j < var; j++)
			if (A[i][j] != 0)
				temp -= A[i][j] * X[j];
		if (temp % A[i][i] != 0) 
			return -2; // 说明有浮点数解，但无整数解.
		X[i] = temp / A[i][i];
	}
	return 0;
}

int main(void)
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int i, j;
	int equ, var;
	while (scanf("%d %d", &equ, &var) != EOF) {
		memset(A, 0, sizeof(A));
		for (i = 0; i < equ; i++)
			for (j = 0; j < var + 1; j++)
				scanf("%d", &A[i][j]);

		int free_num = Gauss(equ, var);
		if (free_num == -1) 
			printf("无解!\n");
		else if (free_num == -2) 
			printf("有浮点数解，无整数解!\n");
		else if (free_num > 0) {
			printf("无穷多解! 自由变元个数为%d\n", free_num);
			for (i = 0; i < var; i++)
				if (freeX[i])
					printf("x%d 是不确定的\n", i + 1);
				else
					printf("x%d: %d\n", i + 1, X[i]);
			
		}
		else 
			for (i = 0; i < var; i++)
				printf("x%d: %d\n", i + 1, X[i]);
		
		printf("\n");
	}
	return 0;
}