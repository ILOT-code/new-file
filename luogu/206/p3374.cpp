#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 500000 + 10;
int n, m, a[maxn], t[maxn];
inline int lowbit(int x) { return x & (-x); }

void add(int x, int k) {
	while (x <= n) {
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
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		t[i] += a[i];
		int j = i + lowbit(i);
		if (j <= n) t[j] += t[i];
	}
	for (int i = 1; i <= m; ++i) {
		int f, x, y;
		scanf("%d%d%d", &f, &x, &y);
		if (f == 1) add(x, y);
		else printf("%d\n", getsum(y) - getsum(x - 1));
	}
	return 0;
}