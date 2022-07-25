//画图容易发现，对角线共线最优。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int main() {
	int n;
	while (~scanf("%d", &n) && n) {
		double x1, y1, x2, y2, temp, l = 0, ans = 0;
		scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
		for (int i = 0; i < n; ++i) {
			scanf("%lf", &temp);
			l += temp;
			ans -= temp * temp / 2;
		}
		double k1 = y1 / x1, k2 = y2 / x2;
		if (k2 > k1) swap(k1, k2);
		x1 = (k2 + 1) * l / (k1 - k2), y1 = k1 * x1;
		x2 = (k1 + 1) * l / (k1 - k2), y2 = k2 * x2;
		ans += (x2 * y1 - x1 * y2) / 2;
		printf("%.3lf\n", ans);
	}
	return 0;
}