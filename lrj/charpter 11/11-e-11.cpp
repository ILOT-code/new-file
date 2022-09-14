#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;

const int maxn = 200000 + 10;
int n, p[maxn], cnt[maxn];
LL sum[maxn];//sum[i]表示当前以i为代表元的点集合中，最大的容量。
int find(int x) { return p[x] != x ? p[x] = find(p[x]) : x;}

struct Edge {
	int from, to, cost;
	Edge(int u = 0, int v = 0, int c = 0) : from(u), to(v), cost(c) {}
	bool operator < (const Edge& rhs) const { return cost > rhs.cost; }
} e[maxn];

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i) p[i] = i, cnt[i] = 1, sum[i] = 0;
		for (int i = 0; i < n - 1; ++i)
			scanf("%d%d%d", &e[i].from, &e[i].to, &e[i].cost);

		sort(e, e + n - 1);
		for (int i = 0; i < n - 1; ++i) {
			int u = find(e[i].from), v = find(e[i].to), c = e[i].cost;
			LL tmp1 = sum[u] + 1LL * cnt[v] * c;
			LL tmp2 = sum[v] + 1LL * cnt[u] * c;
			//在新合并的两个点集中，中心城市是原来两点集的中心城市 最优。
			if (tmp1 > tmp2) {
				p[v] = u;
				sum[u] = tmp1;
				cnt[u] += cnt[v];
			}
			else {
				p[u] = v;
				sum[v] = tmp2;
				cnt[v] += cnt[u];
			}
		}
		printf("%lld\n", sum[find(1)]);
	}
	return 0;
}
