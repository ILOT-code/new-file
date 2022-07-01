#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
int n, m, ans;

void update(int u, int v) {
	int x = ceil((double)(n * v + 1) / (u + v));
	int temp = u * x - v * (n - x);
	if (temp < ans) ans = temp;
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		ans = INF;
		for (int i = 0; i < m; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			update(u, v);
		}
		printf("%d\n", ans);
	}
	return 0;
}