#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 500 + 5;

int n, m, cnt, p[maxn];
struct Point {
	int x, y;
} po[maxn];
struct Edge {
	int u, v, w;
	bool operator<(const Edge& rhs) { return w < rhs.w; }
} e[maxn * maxn];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]);}

void add_edge(int u, int v) {
	e[cnt++] = Edge{u, v, (po[u].x - po[v].x)*(po[u].x - po[v].x) + (po[u].y - po[v].y)*(po[u].y - po[v].y)};
}

void krus() {
	for (int i = 1; i <= n; ++i) p[i] = i;
	sort(e, e + cnt);
	int cnt1 = 0;
	for (int i = 0; i < cnt; ++i) {
		int x = find(e[i].u), y = find(e[i].v);
		if (x == y) continue;
		cnt1++; p[x] = y;
		if (cnt1 == n - m) {
			printf("%.2lf", sqrt(e[i].w));
			break;
		}
	}
}

int main() {
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &po[i].x, &po[i].y);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j < i; ++j)
			add_edge(i, j);
	krus();
	return 0;
}