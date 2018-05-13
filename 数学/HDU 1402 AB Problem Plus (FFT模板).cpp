// HDU 1402 A*B Problem Plus
// 多项式乘法
// FFT

#include <complex>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const double PI = 4 * atan(1);

void bitReverse(complex<double> A[], int len)
{
	int i, j, k;
	for (i = 1, j = len / 2; i < len - 1; i++) {
		if (i < j)
			std::swap(A[i], A[j]);
		//交换互为小标反转的元素，i < j保证交换一次
		//i做正常的+1，j做反转类型的+1,始终保持i和j是反转的
		k = len / 2;
		while (j >= k) {
			j -= k;
			k /= 2;
		}
		if (j < k) 
			j += k;
	}
}

void FFT(complex<double> A[], int N, int on)
{
	bitReverse(A, N);
	for (int m = 2; m <= N; m <<= 1) {
		complex<double> wn(cos(on * 2 * PI / m), sin(on * 2 * PI / m));
		for (int k = 0; k < N; k += m) {
			complex<double> w(1, 0);
			for (int j = k; j < k + m / 2; j++) {
				complex<double> t = w * A[j + m / 2];
				complex<double> u = A[j];			
				A[j] = u + t;
				A[j + m / 2] = u - t;
				w = w * wn;
			}
		}
	}
	if (on == -1)
		for (int i = 0; i < N; i++)
			A[i] /= N;
}

#define MAXN 150000
char strA[MAXN], strB[MAXN];
complex<double> A[MAXN], B[MAXN];
int result[MAXN];

int main()
{
	while (scanf("%s %s", strA, strB) == 2) {
		int lenA = strlen(strA), lenB = strlen(strB);
		int len = std::max(lenA, lenA) << 1;  // 因为结果的长度是2 * len
		int N = 1, i;
		while (N < len) 
			N <<= 1;
		for (i = 0; i < lenA; ++i) 
			A[i] = complex<double>(strA[lenA - i - 1] - '0', 0);
		for (; i < N; ++i)
			A[i] = complex<double>(0, 0);
		for (i = 0; i < lenB; ++i)
			B[i] = complex<double>(strB[lenB - i - 1] - '0', 0);
		for (; i < N; ++i)
			B[i] = complex<double>(0, 0);
		FFT(A, N, 1);
		FFT(B, N, 1);
		for (i = 0; i < N; ++i)
			A[i] = A[i] * B[i];
		FFT(A, N, -1);
		for (i = 0; i< N; i++) 
			result[i] = (int)(A[i].real() + 0.5);
		for (i = 0; i< N; i++) {
			result[i + 1] += result[i] / 10;
			result[i] %= 10;
		}
		for (i = lenA + lenB - 1; result[i] <= 0 && i > 0; --i)
			continue;
		for (; i >= 0; i--)
			putchar(result[i] + '0');
		putchar('\n');
	}
}