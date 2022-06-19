#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 64;
int kase, n, d, K[maxn], zcnt, ocnt, Z[maxn], O[maxn];
unsigned long long k, f[maxn][maxn], maxv, minv;

bool crz(int i, int j) {
	return i < zcnt && (j == ocnt || O[j] + d >= Z[i]);
}
bool cro(int i, int j) {
	return j < ocnt && (i == zcnt || Z[i] + d >= O[j]);
}

unsigned long long  dp(int ii, int jj) {
	if (ii < 0 || jj < 0) return 0;
	unsigned long long  &ans = f[ii][jj];
	if (ans) return ans;
	if (crz(ii - 1, jj)) ans += dp(ii - 1, jj);
	if (cro(ii, jj - 1)) ans += dp(ii, jj - 1);
	return ans;
}

void solve() {
	zcnt = ocnt = 0;
	for (int i = 0; i < n; ++i) {
		if (K[i] == 1) O[ocnt++] = i;
		else Z[zcnt++] = i;
	}

	maxv = minv = 0;
	int ii = 0, jj = 0;
	while (ii < zcnt || jj < ocnt) {
		if (cro(ii, jj)) {maxv = maxv * 2 + 1; jj++;}
		else {maxv = maxv * 2; ii++;}
	}
	ii = jj = 0;
	while (ii < zcnt || jj < ocnt) {
		if (crz(ii, jj)) {minv = minv * 2; ii++;}
		else {minv = minv * 2 + 1; jj++;}
	}

	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	printf("Case %d: %llu %llu %llu\n", ++kase,	dp(zcnt, ocnt), minv, maxv);
}

int main() {
	kase = 0;
	while (~scanf("%d%d%llu", &n, &d, &k) && n) {
		for (int i = 0; i < n; i++) {
			K[n - 1 - i] = k % 2; k = k / 2;
		}
		solve();
	}
	return 0;
}