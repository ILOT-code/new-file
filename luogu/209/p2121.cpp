#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n, m, k, p[maxn];

struct Edge {
	int u, v, w;
	bool operator<(const Edge& rhs) { return w > rhs.w;}
} e[maxn];
int find(int x) { return p[x] == x ? x : p[x] = find(p[x]);}
void krus() {
	sort(e, e + m);
	int cnt1 = 0, ans = 0;
	for (int i = 0; i < m; ++i) {
		int x = find(e[i].u), y = find(e[i].v);
		if (x == y) continue;
		cnt1++; p[x] = y;
		ans += e[i].w;
		if (cnt1 == k) break;
	}
	printf("%d\n", ans);
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < m; ++i) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
	for (int i = 1; i <= n; ++i) p[i] = i;
	krus();
	return 0;
}