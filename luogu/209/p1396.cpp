#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 5;
const int maxm = 20000 + 5;

int n, m, s, t, p[maxn];

int find(int x) { return p[x] == x ? x : p[x] = find(p[x]);}

struct Edge {
	int u, v, w;
	bool operator<(const Edge& rhs) { return w < rhs.w;}
} e[maxm];

void krus() {
	sort(e, e + m);
	int cnt1 = 0;
	for (int i = 0; i < m; ++i) {
		int x = find(e[i].u), y = find(e[i].v);
		if (x == y) continue;
		cnt1++;
		p[x] = y;
		if (find(s) == find(t)) {
			printf("%d\n", e[i].w);
			break;
		}
		if (cnt1 == n - 1) break;
	}
}
int main() {
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for (int i = 0; i < m; ++i) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
	for (int i = 1; i <= n; ++i) p[i] = i;
	krus();
	return 0;
}