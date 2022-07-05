#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int Max = 10000;
int T, kase, a, b;

int solve() {
	if (b >= 3 * a) return -1;
	int ans = Max;
	double A = a, B = b;
	for (int i = 1; i <= ans; ++i) {
		double dist = double(i - 1) / (i + 1) * (A / B) + A / B;
		int m = 1;
		while (dist < (1 - 1e-6)) {
			dist += (A / B - (1 - dist)) / (m + 1);
			if (m + i - 1 >= ans) break;
			m++;
		}
		ans = min(ans, m + i - 1);
	}
	if (ans >= Max) ans = -1;
	return ans;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &a, &b);
		printf("Case %d: %d\n", ++kase, solve());
	}
	return 0;
}