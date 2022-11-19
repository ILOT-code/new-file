#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 1000000 + 10;
int n, m, a[maxn], t[maxn], maxval;
inline int lowbit(int x) { return x & (-x); }
void add(int x, int k) {
	while (x <= maxval) {
		t[x] += k;
		x += lowbit(x);
	}
}
int getsum(int x) {
	int ans = 0;
	while (x >= 1) {
		ans += t[x];
		x -= lowbit(x);
	}
	return ans;
}
struct Qus {
	int l, r, k, idx, ans;
	bool operator<(Qus& rhs) { return r < rhs.r; }
} Q[maxn];
bool cmp(Qus a, Qus b) { return a.idx < b.idx;}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		maxval = max(maxval, a[i]);
	}

	for (int i = 1; i <= m; ++i) scanf("%d%d%d", &Q[i].l, &Q[i].r, &Q[i].k), Q[i].idx = i;
	sort(Q + 1, Q + 1 + m);

	for (int i = 1, j = 1, k = 1; i <= m; ++i) {
		while (j <= Q[i].r) add(a[j++], 1);
		if (k < Q[i].l) {
			while (k < Q[i].l) add(a[k++], -1);
		}
		else if (k > Q[i].l) while (k > Q[i].l) add(a[--k], 1);
		Q[i].ans = getsum(Q[i].k) - getsum(Q[i].k - 1);
	}
	sort(Q + 1, Q + 1 + m, cmp);
	for (int i = 1; i <= m; ++i) printf("%d\n", Q[i].ans);
	return 0;
}