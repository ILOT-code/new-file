#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

int divide(int &n, int d) {
	int ans = 1;
	while (n % d == 0) {
		ans *= d;
		n /= d;
	}
	return ans;
}

long long int solve(int n) {
	if (n == 1) return 2;
	int cnt = 0, temp = sqrt(n) + 1e-3;
	long long int ans = 0;
	for (int i = 2; i <= temp; ++i)
		if (n % i == 0) {
			ans += divide(n, i);
			cnt++;
		}
	if (n > 1) {cnt++; ans += n;}
	if (cnt <= 1) ans += 1;
	return ans;
}
int main() {
	int kase = 0, n;
	while (~scanf("%d", &n) && n) {
		printf("Case %d: %lld\n", ++kase, solve(n));
	}
	return 0;
}