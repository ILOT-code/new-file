#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 30 + 5;
int n;
double t, d[maxn];

int main() {
	while (~scanf("%d%lf", &n, &t) && n) {
		d[n] = 1 << n;
		for (int i = n - 1; i >= 0; --i) {
			double p0 = (double)(1 << i) / d[i + 1];
			if (p0 < t) p0 = t;
			double p1 = (p0 - t) / (1 - t);
			d[i] = (double)(1 << i) * p1 + (1 + p0) / 2 * d[i + 1] * (1 - p1);
		}
		printf("%.3lf\n", d[0]);
	}
	return 0;
}
