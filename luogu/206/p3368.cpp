#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 500000 + 10;
int n, m, a[maxn], t1[maxn], t2[maxn];

inline int lowbit(int x) { return x & (-x); }

void add(int x, int v) {
	int v1 = x * v;
	while (x <= n) {
		t1[x] += v; t2[x] += v1;
		x += lowbit(x);
	}
}
void add1(int l, int r, int v) {
	add(l, v); add(r + 1, -v);
}

int getsum(int* t, int x) {
	int ans = 0;
	while (x >= 1) {
		ans += t[x];
		x -= lowbit(x);
	}
	return ans;
}

long long getsum1(int l, int r) {
	return (1ll + r) * getsum(t1, r) - 1ll * l * getsum(t1, l - 1) +
	       (getsum(t2, r) - getsum(t2, l - 1));
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		t1[i] += a[i] - a[i - 1];
		t2[i] += i * (a[i] - a[i - 1]);
		int j = i + lowbit(i);
		if (j <= n) t1[j] += t1[i], t2[j] += t2[i];
	}
	for (int i = 1; i <= m; ++i) {
		int f, x, y, k;
		scanf("%d", &f);
		if (f == 1) {
			scanf("%d%d%d", &x, &y, &k);
			add1(x, y, k);
		}
		if (f == 2) {
			scanf("%d", &x);
			printf("%d\n", getsum(t1, x));
		}
	}
	return 0;
}