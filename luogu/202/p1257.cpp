#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 5;
const double INF = 2e10;
int n;
struct Point {
	double x, y;
	bool operator< (const Point& rhs) {return x < rhs.x || (x == rhs.x && y < rhs.y);}
} p[maxn];
double dist(int i, int j) {return sqrt((p[i].x - p[j].x) * (p[i].x - p[j].x) + (p[i].y - p[j].y) * (p[i].y - p[j].y));}

int tmp[maxn];
double merge(int l, int r) {
	if (l == r) return INF;
	if (l + 1 == r) return dist(l, r);

	int mid = (l + r) / 2;
	double t1 = merge(l, mid), t2 = merge(mid + 1, r);
	double dis = min(t1, t2);

	int pos = 0, m = 0;
	for (int i = l; i <= r; ++i)
		if (fabs(p[i].x - p[mid].x) < dis) {
			if (i == mid) m = pos;
			tmp[pos++] = i;
		}

	for (int i = 0; i <= m; ++i)
		for (int j = m + 1; j < pos; ++j) {
			if (p[tmp[j]].x - p[tmp[i]].x >= dis) break;
			dis = min(dis, dist(tmp[i], tmp[j]));
		}
	return dis;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	sort(p, p + n);
	printf("%.4lf\n", merge(0, n - 1));
	return 0;
}