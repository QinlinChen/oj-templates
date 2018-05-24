#pragma once
#include <vector>
#include <cmath>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <random>
#include <string>

typedef long long LL;

static inline LL mod(LL a, LL b)
{
	LL r = a % b;
	return (r < 0 ? (r + b) : r);
}

static inline LL myAbs(LL a) { return (a < 0) ? -a : a; }

LL gcd(LL a, LL b, LL *px, LL*py)
{
	std::vector<LL> vecQ;
	LL i = 0, k = myAbs(a), j = myAbs(b), q, r;
	// assume k >= j > 0
	while (j != 0) {
		q = k / j;
		r = k - q * j;
		k = j;
		j = r;
		vecQ.push_back(q);
		i++;
	}
	LL gcd = k, x = 1, y = 0, temp;
	while (--i >= 0) {
		temp = x;
		x = y;
		y = temp - vecQ[i] * y;
	}
	if (px)		*px = x = (a < 0 ? -x : x);
	if (py)		*py = y = (b < 0 ? -y : y);
	assert(a*x + b*y == gcd);
	return gcd;
}

void sieveOfEratosthenes(int N, std::vector<int> &primes)
{
	bool *isPrime = new bool[N + 1];
	for (int i = 2; i <= N; ++i)
		isPrime[i] = true;
	int sqrtN = (int)sqrt((double)N);
	for (int i = 2; i <= sqrtN; ++i) 
		if (isPrime[i]) 
			for (int j = i; i * j <= N; ++j)
				isPrime[i * j] = false;
	for (int i = 2; i <= N; ++i)
		if (isPrime[i])
			primes.push_back(i);
	delete[] isPrime;
}

void sieveOfEular(int N, std::vector<int> &primes)
{
	bool *isPrime = new bool[N + 1];
	for (int i = 2; i <= N; ++i)
		isPrime[i] = true;
	for (int i = 2; i <= N; ++i) {
		if (isPrime[i])
			primes.push_back(i);
		for (int j = 0; j < primes.size() && primes[j] * i <= N; ++j) {
			isPrime[primes[j] * i] = false;
			if (i % primes[j] == 0)
				break;
		}
	}
	delete[] isPrime;
}

LL modularLinerEquationSolver(LL a, LL b, LL n, std::vector<LL> &result)
{
	LL d, x;
	d = gcd(a, n, &x, nullptr);
	if (mod(b, d)) {
		std::cerr << "No solutions" << std::endl;
		return 0;
	}
	LL x0 = mod(x * (b / d), n);
	LL k = n / d;
	for (LL i = 0; i < d; ++i)
		result.push_back(mod(x0 + i * k, n));
	return d;
}

LL mulInverse(LL a, LL n)
{
	LL d, x;
	d = gcd(a, n, &x, nullptr);
	if (d != 1) {
		std::cerr << "No multiplicative inverse" << std::endl;
		exit(0);
	}
	return mod(x, n);
}

int ChineseRemainder(std::vector<int> &A, std::vector<int> &N)
{
	assert(A.size() == N.size());
	int prod = 1;
	for (auto n : N)
		prod *= n;

	int result = 0, m, n;
	for (int i = 0; i < N.size(); ++i) {
		n = N[i];
		m = prod / n;
		result = mod(result + A[i] * (m * mulInverse(m, n)), prod);
	}
	return result;
}
		
LL modPower(LL a, LL pow, LL n)
{
	LL result = 1;
	while (pow) {
		if (pow & 0x1)
			result = (result * a) % n;
		pow >>= 1;
		a = (a * a) % n;
	}
	return result;
}

bool witness(LL a, LL n)
{
	LL u = n - 1;
	int t = 0;
	while (!(u & 0x1)) {
		u >>= 1;
		t++;
	}
	assert(n - 1 == (1LL << t) * u);

	LL x = modPower(a, u, n);
	LL nextx;
	for (int i = 1; i <= t; ++i) {
		nextx = (x * x) % n;
		assert(nextx >= 0);
		if (nextx == 1 && x != 1 && x != n - 1)
			return true;
		x = nextx;
	}
	if (nextx != 1)
		return true;
	return false;
}

static std::default_random_engine e;

bool primeTest(LL number, int tryCount)
{
	assert(number > 0);
	if (!(number & 0x1))
		return false;
	
	std::uniform_int_distribution<LL> u(1, number - 1);
	for (int i = 1; i <= tryCount; ++i) {
		LL a = u(e);
		if (witness(a, number))
			return false;
	}
	return true;
}

LL primeGenerator(int length)
{
	int tryCount = 2 * length * length;
	std::uniform_int_distribution<int> u(0, 1);

	for (int i = 1; i <= tryCount; ++i) {
		LL n = 1;
		for (int j = 1; j <= length - 2; ++j)
			n = (n << 1) + u(e);
		n = (n << 1) + 1;
		if (primeTest(n, length))
			return n;
	}
	return -1;
}

void encode(std::istream &src, std::ostream &dst, LL e, LL n)
{
	src.seekg(0, src.end);
	LL size = src.tellg();
	src.seekg(0);
	char *srcBuf = new char[size];
	src.read(srcBuf, size);

	LL *dstBuf = new LL[size];
	for (LL i = 0; i < size; ++i)
		dstBuf[i] = modPower((LL)(unsigned char)srcBuf[i], e, n);

	dst.write((char *)dstBuf, sizeof(LL) * size);

	delete[] srcBuf;
	delete[] dstBuf;
}

void decode(std::istream &src, std::ostream &dst, LL d, LL n)
{
	src.seekg(0, src.end);
	LL size = src.tellg();
	src.seekg(0);
	assert(size % sizeof(LL) == 0);
	size /= sizeof(LL);

	LL *srcBuf = new LL[size];
	src.read((char *)srcBuf, size * sizeof(LL));

	char *dstBuf = new char[size];
	for (LL i = 0; i < size; ++i)
		dstBuf[i] = (char)modPower(srcBuf[i], d, n);

	dst.write((char *)dstBuf, size);

	delete[] srcBuf;
	delete[] dstBuf;
}

static LL modKey = 2333 * 23333;
static LL encryptKey = 21250345;
static LL decryptKey = 233;

void encryptFile(std::string srcfile, std::string dstfile)
{
	std::ifstream fin(srcfile, std::ifstream::binary);
	std::ofstream fout(dstfile, std::ofstream::binary);
	encode(fin, fout, encryptKey, modKey);
}

void decryptFile(std::string srcfile, std::string dstfile)
{
	std::ifstream fin(srcfile, std::ifstream::binary);
	std::ofstream fout(dstfile, std::ofstream::binary);
	decode(fin, fout, decryptKey, modKey);
}