#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 5;
int n, m, flag[maxn];
vector<int> primes;
vector<int> cnt;
vector<int> ans;

void prime_factors(int n) {
	primes.clear();
	cnt.clear();
	int temp = sqrt(n) + 1e-3;
	for (int i = 2; i <= temp; ++i) {
		if (n % i == 0) {
			primes.push_back(i);
			int t = 0;
			while (n % i == 0) {n /= i; t++;}
			cnt.push_back(t);
		}
	}
	if (n > 1) {
		primes.push_back(n);
		cnt.push_back(1);
	}
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		prime_factors(m);
		memset(flag, 0, sizeof(flag));
		n--;
		for (int i = 0; i < primes.size(); ++i) {
			int p = primes[i], c = cnt[i], e = 0;
			for (int k = 1; k <= n; ++k) {
				int x = n - k + 1;
				while (x % p == 0) {x /= p; e++;}
				x = k;
				while (x % p == 0) {x /= p; e--;}
				if (e < c) flag[k] = 1;
			}
		}
		ans.clear();
		for (int k = 1; k <= n; k++)
			if (!flag[k]) ans.push_back(k + 1);
		printf("%d\n", ans.size());
		if (!ans.empty()) {
			printf("%d", ans[0]);
			for (int i = 1; i < ans.size(); ++i) printf(" %d", ans[i]);
		}
		printf("\n");
	}
	return 0;
}