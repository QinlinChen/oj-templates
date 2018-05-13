// poj 2689 Prime Distance
// 筛[L, U] (L < U < 2147483647)之间的素数
// 先筛出[0, sqrt(2^31)]之间的素数
// 用这些素数来筛[L, U]

#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>
using namespace std;

typedef long long LL;

void sieveOfEratosthenes(LL N, std::vector<LL> &primes)
{
	bool *isPrime = new bool[N + 1];
	for (LL i = 2; i <= N; ++i)
		isPrime[i] = true;
	LL sqrtN = (LL)sqrt((double)N);
	for (LL i = 2; i <= sqrtN; ++i)
		if (isPrime[i])
			for (LL j = i * i; j <= N; j += i)
				isPrime[j] = false;
	for (LL i = 2; i <= N; ++i)
		if (isPrime[i])
			primes.push_back(i);
	delete[] isPrime;
}

vector<LL> primesLessThan50000;
bool isPrime[1000010];

void sieveBetweenLU(LL L, LL U, std::vector<LL> &primes)
{
	memset(isPrime, true, sizeof(isPrime));
	if (L < 2)
		L = 2;
	for (LL i = 0; i < primesLessThan50000.size(); ++i) {
		LL sieve = primesLessThan50000[i];
		if (sieve > U)
			break;
		LL begin = L / sieve + (L % sieve ? 1 : 0);
		if (begin == 1)
			begin++;
		for (LL j = begin * sieve; j <= U; j += sieve)
			isPrime[j - L] = false;
	}
	for (LL i = L; i <= U; ++i)
		if (isPrime[i - L])
			primes.push_back(i);
}

int main()
{
	ios::sync_with_stdio(false);
	LL L, U;
	sieveOfEratosthenes(50000, primesLessThan50000);

	while (cin >> L >> U) {
		vector<LL> primesBetweenLU;
		LL C1, C2, minD, D1, D2, maxD;
		sieveBetweenLU(L, U, primesBetweenLU);
		if (primesBetweenLU.size() < 2)
			cout << "There are no adjacent primes." << endl;
		else {
			C1 = D1 = primesBetweenLU[0];
			C2 = D2 = primesBetweenLU[1];
			minD = C2 - C1;
			maxD = D2 - D1;
			for (int i = 2; i < primesBetweenLU.size(); ++i) {
				int distance = primesBetweenLU[i] - primesBetweenLU[i - 1];
				if (distance < minD) {
					C2 = primesBetweenLU[i];
					C1 = primesBetweenLU[i - 1];
					minD = distance;
				}
				if (distance > maxD) {
					D2 = primesBetweenLU[i];
					D1 = primesBetweenLU[i - 1];
					maxD = distance;
				}
			}
			cout << C1 << "," << C2 << " are closest, "
				<< D1 << "," << D2 << " are most distant." << endl;
		}
	}
}