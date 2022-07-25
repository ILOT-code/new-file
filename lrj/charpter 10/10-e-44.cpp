#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int T, n, k;

int solve() {
	int sign = 1, ans = 0;
	while (n) {
		ans += sign * n;
		n /= k;
		sign = -sign;
	}
	return ans;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		printf("%d\n", solve());
	}
	return 0;
}