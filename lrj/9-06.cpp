//有两次贪心
//1: 一种灯要不全替换，要不全不替换
//2: 替换只能是连续的，不可能里散开来。
//例如原电压排布是 1 2 3 4 5 6，只能换成 2 2 3 6 6 6 这样的排布，不可错位。
//在以上的限制下，动态规划的状态转移方程就很好设计了。

#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 5;
struct Lamp {
	int v, k, c, l;
	bool operator < (const Lamp& rhs) const {
		return v < rhs.v;
	}
} lamp[maxn];
int n, num[maxn], d[maxn];

int main() {
	while (~scanf("%d", &n) && n ) {
		for (int i = 1; i <= n ; ++i) scanf("%d%d%d%d", &lamp[i].v, &lamp[i].k, &lamp[i].c, &lamp[i].l);
		sort(lamp + 1, lamp + n + 1);
		num[0] = 0;
		for (int i = 1; i <= n; ++i) num[i] = num[i - 1] + lamp[i].l;
		d[0] = 0;
		for (int i = 1; i <= n; ++i) {
			d[i] = num[i] * lamp[i].c + lamp[i].k;
			for (int j = 1; j < i; ++j)
				d[i] = min(d[i], d[j] + (num[i] - num[j]) * lamp[i].c + lamp[i].k);
		}
		printf("%d\n", d[n]);
	}
	return 0;
}