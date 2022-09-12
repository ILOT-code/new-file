#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
typedef pair<double, int> PDI;

const double eps = 1e-8;
const int INF = 0x3f3f3f3f;
const int maxn = 2000 + 5;
int kase, n, F;
double G[maxn][maxn];

struct Point {
	double x, y;
	Point(double x = 0, double y = 0): x(x), y(y) {}
	Point operator+(const Point& rhs) {return Point(x + rhs.x, y + rhs.y);};
	Point operator-(const Point& rhs) {return Point(x - rhs.x, y - rhs.y);};
	Point operator*(double k) {return Point(k * x, k * y);}
	double cros(const Point& rhs) {return x * rhs.y - y * rhs.x;}
	double Mul(const Point& rhs) { return x * rhs.x + y * rhs.y;}
	double length() {return sqrt(x * x + y * y);}

	Point VerticalNormalize() {
		double L = length();
		return Point(-y / L, x / L);
	}
	Point Rotate(double angle) {
		Point t;
		t.x = x * cos(angle) - y * sin(angle);
		t.y = y * cos(angle) + x * sin(angle);
		return t;
	}
};
vector<Point> pts;

double calc_scale(Point a, Point b, Point c, Point v) {
	Point ab = b - a;
	Point bc = c - b;
	return (v.cros(ab)) / (bc.cros(v));
}
bool onSegment(Point x, Point a, Point b) {
	return (fabs((x - a).cros(x - b)) <= eps) && ((x - a).Mul(x - b) < eps);
}

void pretreatment() {
	double thyta = asin(1.0 / F);
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j < n; ++j) {
			Point tmp = pts[j + 1] - pts[j];
			tmp = tmp.VerticalNormalize();
			Point up = tmp.Rotate(thyta), down = tmp.Rotate(-thyta);
			double scale1 = calc_scale(pts[i], pts[j], pts[j + 1], up);
			double scale2 = calc_scale(pts[i], pts[j], pts[j + 1], down);
			if (scale1 - eps > 0 && scale1 + eps < 1) {
				Point now = pts[j] + (pts[j + 1] - pts[j]) * scale1;
				pts.push_back(now);
			}
			if (scale2 - eps > 0 && scale2 + eps < 1) {
				Point now = pts[j] + (pts[j + 1] - pts[j]) * scale2;
				pts.push_back(now);
			}
		}

	int cnt = pts.size();
	for (int i = 0; i < cnt; ++i)
		for (int j = 0; j < cnt; ++j) {
			bool flag = false;
			for (int k = 0; k < n; ++k)
				if (onSegment(pts[i], pts[k], pts[k + 1]) && onSegment(pts[j], pts[k], pts[k + 1])
				        && (pts[i] - pts[k]).length() < (pts[j] - pts[k]).length()) {flag = true; break;}
			if (flag) G[i][j] = (pts[j] - pts[i]).length();
			else G[i][j] = F * (pts[j] - pts[i]).length();
		}
}

bool vis[maxn];
double d[maxn];
double dijkstra() {
	for (int i = 0; i < pts.size(); ++i) d[i] = INF, vis[i] = 0;
	priority_queue<PDI, vector<PDI>, greater<PDI>> Q;
	Q.push(PDI(d[0] = 0.0, 0));

	while (!Q.empty()) {
		int u = Q.top().second; Q.pop();
		if (u == n) break;
		if (vis[u]) continue;
		vis[u] = true;
		for (int v = 0; v < pts.size(); ++v)
			if (!vis[v] && d[v] > d[u] + G[u][v])
				Q.push(PDI(d[v] = d[u] + G[u][v], v));
	}
	return d[n];
}

int main() {
	while (~scanf("%d%d", &n, &F) && n && F) {
		pts.clear();
		for (int i = 0; i <= n; ++i) {
			double a, b; scanf("%lf%lf", &a, &b);
			pts.push_back(Point(a, b));
		}
		pretreatment();
		printf("Case %d: %.3lf\n", ++kase, dijkstra());
	}
	return 0;
}
