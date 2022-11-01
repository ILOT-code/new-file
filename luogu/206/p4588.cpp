#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100000 + 10;

int T, Q, M;
LL d[maxn << 2];

void build(int p, int s, int t) {
	if (s == t) {d[p] = 1; return;}
	int m = (s + t) >> 1;
	build(2 * p, s, m); build(2 * p + 1, m + 1, t);
	d[p] = (d[2 * p] * d[2 * p + 1]) % M;
}

void update(int l, int r, int c, int s, int t, int p) {
	if (s >= l && t <= r) {d[p] = c % M; return;}
	int m = (s + t) >> 1;
	if (m >= l) update(l, r, c, s, m, 2 * p);
	if (m < r) update(l, r, c, m + 1, t, 2 * p + 1);
	d[p] =  (d[2 * p] * d[2 * p + 1]) % M;
}

LL getmul(int l, int r, int s, int t, int p) {
	if (s >= l && t <= r) {return d[p] % M;}
	int m = (s + t) >> 1;
	LL ret = 1;
	if (m >= l) ret *= getmul(l, r, s, m, 2 * p);
	if (m < r) ret *= getmul(l, r, m + 1, t, 2 * p + 1);
	return ret % M;
}
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &Q, &M);
		build(1, 1, Q);
		for (int i = 1, f, x; i <= Q; ++i) {
			scanf("%d%d", &f, &x);
			if (f == 1) update(i, i, x, 1, Q, 1);
			else update(x, x, 1, 1, Q, 1);
			printf("%lld\n", getmul(1, i, 1, Q, 1));
		}
	}
	return 0;
}