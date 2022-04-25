#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

const int maxn = 100005;
int L, n;
double d;

struct Node {
	double l, r;
	bool operator<(const Node &x) const {
		return fabs(x.r - r) < 1e-8 ? l > x.l : r < x.r;
	}
} nodes[maxn];

int main() {
	while (~scanf("%d%lf%d", &L, &d, &n)) {
		for (int i = 0; i < n; ++i) {
			double x, y, dx;
			scanf("%lf%lf", &x, &y);
			dx = sqrt(d * d - y * y);
			nodes[i].l = x - dx;
			nodes[i].r = x + dx;
		}
		sort(nodes, nodes + n);
		int ans = 1;
		double pos = nodes[0].r;
		for (int i = 1; i < n; ++i) {
			if (nodes[i].l - 1e-8 < pos) continue;
			pos = nodes[i].r;
			ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
