#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 64;
int kase, n, d, K[maxn], zcnt, ocnt, Z[maxn], O[maxn];
unsigned long long k, f[maxn][maxn], maxv, minv;

bool crz(int i, int j) {
	return i < zcnt && (j == ocnt || O[j] + d >= Z[i]);
	//应该是i < zcnt && Z[i] + d >= O[j - 1] && (j == ocnt || O[j] + d >= Z[i])，但O[j]+d>=O[j-1]-d显然成立。则化简了。
}
bool cro(int i, int j) {
	return j < ocnt && (i == zcnt || Z[i] + d >= O[j]);
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
	for (int i = 0; i <= zcnt; ++i)
		for (int j = 0; j <= ocnt; ++j)
			if (f[i][j]) {
				if (crz(i, j)) f[i + 1][j] += f[i][j];
				if (cro(i, j)) f[i][j + 1] += f[i][j];
			}
	printf("Case %d: %llu %llu %llu\n", ++kase, f[zcnt][ocnt], minv, maxv);
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