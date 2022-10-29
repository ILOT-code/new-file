#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000000 + 10;
int n, m, d[maxn][21], Log[maxn];
inline int read() {
	char c = getchar(); int x = 0, f = 1;
	while (c < '0' || c > '9') {if (c == '-')f = -1; c = getchar();}
	while (c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = getchar();}
	return x * f;
}
int main() {
	n = read(), m = read();
	Log[1] = 0, Log[2] = 1;
	for (int i = 3; i <= n; ++i) Log[i] = Log[i / 2] + 1;
	for (int i = 1; i <= n; ++i) d[i][0] = read();
	for (int j = 1; j <= Log[n]; ++j)
		for (int i = 1; i + (1 << j) - 1 <= n; ++i)
			d[i][j] = max(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
	for (int i = 1; i <= m; ++i) {
		int l = read(), r = read();
		int k = Log[r - l + 1];
		printf("%d\n", max(d[l][k], d[r - (1 << k) + 1][k]) );
	}
	return 0;
}