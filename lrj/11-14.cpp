//每一条边看成数轴上的点，位置对应的数是它的长度。这些点会运动，相邻点会碰撞。
//最小生成树就是选取了从小到大合法的n-1个点。
//只有有两个点相互碰撞后，最小生成数才有可能改变。
//设接下来是两个非MST中的点相碰，则它们之间没有MST中的点，易得，最小生成树不变。
//若是两个MST中的点相碰，则它们之间没有非MST中的点，易得，最小生成树不变。
//若一个MST中点与一个非MST中点相碰，如果MST中点向左，非点向右，
//则在选取最小生成树的边时依旧不会发生变化，都是选取了该MST中点后，跳过了另一点。
//则只有一个MST中点向右与一个非MST中点向左相碰，可能发生变化。
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 50 + 5;
const int maxks = maxn * (maxn + 1) / 2;
const double eps = 1e-8;
int kase, n, nks;

struct KineticPoint {
	double x, y, z;
	double dx, dy, dz;
	void read() { scanf("%lf%lf%lf%lf%lf%lf", &x, &y, &z, &dx, &dy, &dz); }
} kp[maxn];

struct KineticSegment {
	double a, b, c;
	int u, v;
	bool operator<(const KineticSegment& rhs) const { return c < rhs.c; }
} ks[maxks];

struct Event {
	double t;
	int newks, oldks;
	Event(double t, int newks, int oldks): t(t), newks(newks), oldks(oldks) {}
	bool operator<(const Event& rhs) const { return t < rhs.t; }
};
vector<Event> events;

inline double sqr(double x) { return x * x; }
void make_segments() {
	nks = 0;
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j) {
			ks[nks].a = sqr(kp[i].dx - kp[j].dx) + sqr(kp[i].dy - kp[j].dy) + sqr(kp[i].dz - kp[j].dz);
			ks[nks].b = 2 * ((kp[i].dx - kp[j].dx) * (kp[i].x - kp[j].x) + (kp[i].dy - kp[j].dy) * (kp[i].y - kp[j].y) + (kp[i].dz - kp[j].dz) * (kp[i].z - kp[j].z));
			ks[nks].c = sqr(kp[i].x - kp[j].x) + sqr(kp[i].y - kp[j].y) + sqr(kp[i].z - kp[j].z);
			ks[nks].u = i;
			ks[nks].v = j;
			nks++;
		}
	sort(ks, ks + nks);
}

void make_events() {
	events.clear();
	for (int i = 0; i < nks; ++i)
		for (int j = i + 1; j < nks; ++j) {
			double a = ks[i].a - ks[j].a;
			double b = ks[i].b - ks[j].b;
			double c = ks[i].c - ks[j].c;
			if (fabs(a) < eps) {
				if (fabs(b) < eps) continue;
				if (b < 0 && c > 0) events.push_back(Event(-c / b, i, j));
				if (b > 0 && c < 0) events.push_back(Event(-c / b, j, i));
			}
			else {
				double delta = b * b - 4 * a * c;
				if (delta < eps) continue;
				delta = sqrt(delta);
				double t1 = (-b - delta) / (2 * a);
				double t2 = (-b + delta) / (2 * a);
				if (t1 > 0) events.push_back(Event(t1, i, j));
				if (t2 > 0) events.push_back(Event(t2, j, i));
			}
		}
	sort(events.begin(), events.end());
}

int pa[maxn];
void init() { for (int i = 0; i < n; ++i) pa[i] = i;}
int find(int x) { return pa[x] != x ? pa[x] = find(pa[x]) : x;}
int solve() {
	int pos[maxks], e[maxn];
	init();
	for (int i = 0; i < nks; ++i) pos[i] = 0;
	int idx = 0;
	for (int i = 0; i < nks; ++i) {
		int u = find(ks[i].u), v = find(ks[i].v);
		if (u != v) {
			pos[i] = ++idx;
			e[idx] = i;
			pa[u] = v;
		}
		if (idx == n - 1) break;
	}

	int ans = 1;
	for (int i = 0; i < events.size(); ++i) {
		if (pos[events[i].oldks] && !pos[events[i].newks]) {
			init();
			int oldpos = pos[events[i].oldks];
			for (int j = 1; j < n; ++j) {
				if (j != oldpos) {
					int u = find(ks[e[j]].u), v = find(ks[e[j]].v);
					if (u != v) pa[u] = v;
				}
			}
			int u = find(ks[events[i].newks].u), v = find(ks[events[i].newks].v);
			if (u != v) {
				ans++;
				e[oldpos] = events[i].newks;
				pos[events[i].newks] = oldpos;
				pos[events[i].oldks] = 0;
			}
		}
	}
	return ans;
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) kp[i].read();
		make_segments();
		make_events();
		printf("Case %d: %d\n", ++kase, solve());
	}
	return 0;
}