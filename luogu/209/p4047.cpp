#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef pair<int, int> PII;
#define fi first
#define se second
const int maxn = 1000 + 5;
int n, k, cnt, p[maxn];
PII po[maxn];
struct Edge {
	int u, v, d;
	bool operator<(Edge& rhs) {return d < rhs.d;}
} e[maxn * maxn];
int dist(int i, int j) {return (po[i].fi - po[j].fi) * (po[i].fi - po[j].fi) + (po[i].se - po[j].se) * (po[i].se - po[j].se);}
int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
void krus() {
	sort(e, e + cnt);
	int cnt1 = 0;
	for (int i = 0; i < cnt; ++i) {
		int x = find(e[i].u), y = find(e[i].v);
		if (x == y) continue;
		cnt1++;
		p[x] = y;
		if (cnt1 == n - k + 1) {
			printf("%.2lf\n", sqrt(e[i].d));
			break;
		}
	}
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++i) p[i] = i;
	for (int i = 0; i < n; ++i) scanf("%d%d", &po[i].fi, &po[i].se);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < i; ++j)
			e[cnt++] = Edge{i, j, dist(i, j)};
	krus();
	return 0;
}