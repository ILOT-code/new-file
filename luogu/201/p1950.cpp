#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 5;
int n, m, g[maxn][maxn], h[maxn];
long long ans;

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i, getchar())
		for (int j = 1; j <= m; ++j) {
			char c; cin >> c;
			if (c == '*') g[i][j] = 1;
		}

	int st[maxn], top, l[maxn], r[maxn];
	h[0] = h[m + 1] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) h[j] = g[i][j] ? 0 : h[j] + 1;
		top = 0;
		for (int j = m + 1; j >= 0; --j) {
			while (top && h[j] <= h[st[top]]) l[st[top--]] = j;
			st[++top] = j;
		}

		top = 0;
		for (int j = 0; j <= m + 1; ++j) {
			while (top && h[j] < h[st[top]]) r[st[top--]] = j;
			st[++top] = j;
		}
		for (int j = 1; j <= m; ++j) ans += 1ll * (j - l[j]) * (r[j] - j) * h[j];
	}
	printf("%lld\n", ans);
	return 0;
}