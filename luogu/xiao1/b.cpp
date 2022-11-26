#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000000 + 5;
const int INF = 1000000000 + 20;
int n, d[maxn], g[maxn];
struct Point {
	int x, y;
	bool operator<(Point& rhs) { return x < rhs.x;}
} po[maxn];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		po[i].x = x, po[i].y = y;
	}
	po[0].x = po[0].y = 0;
	po[n + 1].x = po[n + 1].y = INF;
	sort(po, po + n + 2);
	for (int i = 0; i <= n + 2; ++i) g[i] = INF+100;
	int ans = 0;
	for (int i = 0; i <= n + 1; ++i) {
		int k = upper_bound(g + 1, g + n + 3, po[i].y) - g;
		d[i] = k;
		ans = max(ans, k);
		g[k] = po[i].y;
	}
	printf("%d", ans - 1);
	return 0;
}