#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 200 + 5;
int T, n, A[maxn], d[maxn][maxn][maxn];

int dp(int l, int r, int k) {
	if (l > r) return 0;
	int &ans = d[l][r][k];
	if (ans != -1) return ans;
	int p = r;
	while (p >= l && A[p] == A[r]) p--;
	p++;
	ans = dp(l, p - 1, 0) + (r - p + 1 + k) * (r - p + 1 + k);
	for (int q = l; q < p; ++q) {
		if (A[q] == A[r] && A[q + 1] != A[q])
			ans = max(ans, dp(q + 1, p - 1, 0) + dp(l, q, r - p + 1 + k));
	}
	return ans;
}

int main() {
	scanf("%d", &T);
	int kase = 0;
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%d", &A[i]);
		memset(d, -1, sizeof(d));
		printf("Case %d: %d\n", ++kase, dp(0, n - 1, 0));
	}
	return 0;
}