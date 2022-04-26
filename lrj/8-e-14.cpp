#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 7;
const double eps = 1e-10;
int n;

struct Node {
	int l, r;
	void read() {
		scanf("%d%d", &l, &r);
	}
	bool operator<(const Node &rhs) const {
		return l < rhs.l || (l == rhs.l && r < rhs.r);
	}
} p[maxn];

int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}

int dcmp(double a, double b) {
	if (fabs(a - b) < eps) return 0;
	if (a > b) return 1;
	return -1;
}

bool solve(double mid) {
	double pos = -1.0;
	for (int i = 0; i < n; ++i) {
		if (dcmp(p[i].l, pos) > 0)
			pos = p[i].l + mid;
		else {
			if ((pos + mid) > p[i].r) return false;
			pos += mid;
		}
	}
	return true;
}

int main() {
	while (~scanf("%d", &n)) {
		int Rt = 0x3f3f3f3f;
		for (int i = 0; i < n; ++i) {
			p[i].read();
			Rt = min(Rt, p[i].r - p[i].l);
		}
		sort(p, p + n);
		double L = 0, R = Rt * 1.0;
		while (R - L > eps) {
			double mid = (L + R) / 2.0;
			if (solve(mid)) L = mid;
			else R = mid;
		}
		L = (L + R) / 2.0;
		double err = 1e18;
		int fz, fm;
		for (int i = 1; i <= 100000; ++i) {
			int j = floor(i * L);
			if (dcmp( fabs((j * 1.0) / i - L), err ) == -1) {
				err = fabs((j * 1.0) / i - L);
				fz = j; fm = i;
			}
			j = ceil(i * L);
			if (dcmp( fabs((j * 1.0) / i - L), err ) == -1) {
				err = fabs((j * 1.0) / i - L);
				fz = j; fm = i;
			}
		}
		int g = gcd(fz, fm);
		fz /= g; fm /= g;
		printf("%d/%d\n", fz, fm);
	}
	return 0;
}
