#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 5000 + 10;
int n, d[maxn];

struct Element {
	int l, w;
	Element(int l = 0, int w = 0): l(l), w(w) {}
	bool operator<(const Element& rhs) {
		if (l != rhs.l) return l > rhs.l;
		return w > rhs.w;
	}
	bool operator>(const Element& rhs) {
		return w > rhs.w;
	}
} e[maxn];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d", &e[i].l, &e[i].w);

	sort(e + 1, e + 1 + n);
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < i; ++j)
			if (e[i] > e[j]) d[i] = max(d[i], d[j] + 1);
	int ans = 0;
	for (int i = 1; i <= n; ++i) ans = max(ans, d[i]);
	printf("%d\n", ans);
	return 0;
}