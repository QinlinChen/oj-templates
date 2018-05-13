// poj 1286 Necklace of Beads
// Polya Enumerator Theorem

#include <iostream>
using namespace std;

typedef long long LL;

int gcd(int a, int b) { return (b == 0 ? a : gcd(b, a % b)); }

LL power(LL a, int pow)
{
	LL prod = 1;
	while (pow) {
		if (pow & 0x1)
			prod *= a;
		a *= a;
		pow >>= 1;
	}
	return prod;
}

LL polyaForDihedral(int N, int color)
{
	if (N <= 0)
		return 0;
	LL count = 0;
	for (int s = 0; s < N; ++s) 
		count += power(color, gcd(N, s));
	if (N & 0x1)
		count += N * power(color, (N + 1) / 2);
	else
		count += (N / 2) *(power(color, N / 2) + power(color, N / 2 + 1));
	count /= N * 2;
	return count;
}

int main()
{
	int N;
	while (cin >> N) {
		if (N == -1)
			break;
		cout << polyaForDihedral(N, 3) << endl;
	}
}