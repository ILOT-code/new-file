#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;
int n, ans, d, dp[maxn][maxn];

struct Point {
	int x, y;
	Point(int x = 0, int y = 0): x(x), y(y) {}
	Point operator - (const Point &rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
	bool operator<(const Point &rhs) const;
} points[maxn], center, up[maxn];


int distant(const Point &a) {
	return a.x * a.x + a.y * a.y;
}
int crossProduct(const Point &a, const Point &b) {
	return a.x * b.y - b.x * a.y;
}
bool Point::operator < (const Point &rhs) const {
	int t = crossProduct(*this - center, rhs - center);
	if (t != 0) return t > 0;
	return distant(*this - center) < distant(rhs - center);
}
void solve() {
	memset(dp, 0, sizeof(dp));
	sort(up + 1, up + d + 1);
	for (int i = 2; i <= d; ++i) {
		int j = i - 1;
		while (j && !crossProduct(up[i] - center, up[j] - center)) j--;
		bool merge = (j == (i - 1));
		while (j) {
			int k = j - 1;
			while (k && crossProduct(up[i] - up[k], up[j] - up[k]) > 0) k--;
			int area = crossProduct(up[j] - center, up[i] - center);
			if (k) area += dp[j][k];
			ans = max(ans, area);
			if (merge) dp[i][j] = area;
			j = k;
		}
		if (merge) for (int j = 2; j < i; ++j) dp[i][j] = max(dp[i][j], dp[i][j - 1]);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			scanf("%d%d", &points[i].x, &points[i].y);
		ans = 0;
		for (int i = 0; i < n; ++i) {
			center = points[i];
			d = 0;
			for (int j = 0; j < n; ++j)
				if (points[j].y > center.y || (points[j].y == center.y && points[j].x > center.x))
					up[++d] = points[j];
			solve();
		}
		printf("%.1lf\n", 0.5 * ans);
	}
	return 0;
}