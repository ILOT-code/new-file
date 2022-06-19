#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 105;
int T, n, w, h, dy[maxn];
struct Point {
	int x, y;
	bool operator<(const Point &rhs) const {return x < rhs.x;}
} p[maxn];

void solve() {
	int ansx = 0, ansy = 0, ans = 0;
	int m = unique(dy, dy + n + 2) - dy;
	for (int i = 0; i < m; ++i) {
		for (int j = i + 1; j < m; ++j) {
			int left = 0, hh = dy[j] - dy[i];
			for (int k = 0; k < n; ++k) {
				if (p[k].y <= dy[i] || p[k].y >= dy[j]) continue;
				if (ans < min(hh, p[k].x - left)) {
					ans = min(hh, p[k].x - left);
					ansx = left; ansy = dy[i];
				}
				left = p[k].x;
			}
			if (ans < min(hh, w - left)) {
				ans = min(hh, w - left);
				ansx = left; ansy = dy[i];
			}
		}
	}
	printf("%d %d %d\n", ansx, ansy, ans);
	if (T) printf("\n");
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &w, &h);
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &p[i].x, &p[i].y);
			dy[i] = p[i].y;
		}
		dy[n] = 0; dy[n + 1] = h;
		sort(dy, dy + n + 2);
		sort(p, p + n);
		solve();
	}
	return 0;
}

