// 用费马定理求逆元
#include <cstdio>
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

#define MAXSIZE 100005
#define MOD 9973

string S;
int len;
int prod[MAXSIZE];

void initialize()
{
	len = S.length();
	prod[0] = 1;
	for (int i = 1; i <= len; ++i)
		prod[i] = (prod[i - 1] * ((int)S[i - 1] - 28)) % MOD;
}

int power(int a, int b, int n)
{
	int result = 1;
	while (b) {
		if (b & 0x1)
			result = (result * a) % n;
		b >>= 1;
		a = (a * a) % n;
	}
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	int query, a, b;
	while (cin >> query) {
		cin >> S;
		initialize();
		for (int i = 1; i <= query; ++i) {
			cin >> a >> b;
			// 若mod为素数，那么由费马定理知，a^(-1)=a^(n-2)
			int inverse = power(prod[a - 1], MOD - 2, MOD) % MOD;
			cout << (inverse * prod[b]) % MOD << endl;
		}
	}
}