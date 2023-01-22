#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;

const LL mod = 100003;
LL n, m;


LL quick_pow(LL a, LL b) {
	if (b == 0) return 1;
	if (b == 1) return a % mod;
	bool flag = b % 2;
	LL mid = b / 2, tmp = quick_pow(a, mid);
	if (flag) return tmp * tmp % mod * a % mod;
	else return tmp * tmp % mod;
}

int main() {
	scanf("%lld%lld", &m, &n);
	printf("%lld\n", (quick_pow(m, n) - m % mod * quick_pow(m - 1, n - 1) % mod + mod) % mod) ;
	return 0;
}
