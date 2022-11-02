#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n, m, f[maxn << 2];
double a[maxn], d[maxn << 2];

int getlen(double lmax, int s, int t, int p) {
	if (d[p] <= lmax) return 0;
	if (a[s] > lmax) return f[p];

	int m = (s + t) >> 1;
	if (d[2 * p] <= lmax) return getlen(lmax, m + 1, t, 2 * p + 1);
	else return getlen(lmax, s, m, 2 * p) + f[p] - f[2 * p];
}

void update(int x, int h, int s, int t, int p) {
	if (s == t && s == x) {
		d[p] = a[s];
		f[p] = 1;
		return;
	}
	int m = (s + t) >> 1;
	if (x <= m) update(x, h, s, m, 2 * p);
	else update(x, h, m + 1, t, 2 * p + 1);
	d[p] = max(d[2 * p], d[2 * p + 1]);
	f[p] = f[2 * p] + getlen(d[2 * p], m + 1, t, 2 * p + 1);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		a[x] = double(y) / x;
		update(x, y, 1, n, 1);
		printf("%d\n", f[1]);
	}
	return 0;
}