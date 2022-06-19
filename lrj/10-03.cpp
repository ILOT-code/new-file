#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn = 10000;
vector<int>primes;
int e[maxn];

bool is_prime(int n) {
	int temp = sqrt(n) + 1e-3;
	for (int i = 2; i <= temp; ++i)
		if (n % i == 0) return false;
	return true;
}
void add_integer(int n, int d) {
	for (int i = 0; i < primes.size(); ++i) {
		while (n % primes[i] == 0) {
			n /= primes[i];
			e[i] += d;
		}
		if (n == 1) break;
	}
}
void add_factorial(int n, int d) {
	for (int i = 1; i <= n; ++i)
		add_integer(i, d);
}
int main() {
	for (int i = 2; i <= 10000; ++i)
		if (is_prime(i)) primes.push_back(i);
	int p, q, r, s;
	while (~scanf("%d%d%d%d", &p, &q, &r, &s)) {
		memset(e, 0, sizeof(e));
		add_factorial(p, 1);
		add_factorial(q, -1);
		add_factorial(p - q, -1);
		add_factorial(r, -1);
		add_factorial(s, 1);
		add_factorial(r - s, 1);
		double ans = 1;
		for (int i = 0; i < primes.size(); ++i)
			ans *= pow(primes[i], e[i]);
		printf("%.5lf\n", ans);
	}
	return 0;
}