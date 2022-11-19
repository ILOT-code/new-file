#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 500 + 5;
int A, B, cnt, a[maxn][maxn], p[maxn];

inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]);}

struct Edge {
	int u, v, w;
	bool operator<(const Edge& rhs) { return w < rhs.w; }
} e[maxn * maxn];

void add_edge(int u, int v, int w) { e[cnt++] = Edge{u, v, w}; }

int krus() {
	for (int i = 0; i <= B; ++i) p[i] = i;
	sort(e, e + cnt);

	int cnt1 = 0, ans = 0;
	for (int i = 0; i < cnt; ++i) {
		int x = find(e[i].u), y = find(e[i].v);
		if (x == y) continue;
		cnt1++; p[x] = y;
		ans += e[i].w;
		if (cnt1 == B) break;
	}
	return ans;
}
int main() {
	scanf("%d%d", &A, &B);
	for (int i = 1; i <= B; ++i)
		for (int j = 1; j <= B; ++j)
			scanf("%d", &a[i][j]);

	for (int i = 1; i <= B; ++i)
		for (int j = 1; j < i; ++j)
			if (a[i][j] != 0) add_edge(i, j, a[i][j]);
	for (int i = 1; i <= B; ++i) add_edge(0, i, A);
	printf("%d\n", krus());
}