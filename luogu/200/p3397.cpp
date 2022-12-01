#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 5;
int n, m, d[maxn][maxn];
int main() {
	scanf("%d%d", &n, &m);

	while (m--) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		for (int i = x1; i <= x2; ++i) d[i][y1]++, d[i][y2+1]--;
	}
	for (int i = 1; i <= n; ++i) {
		int sum = 0;
		for (int j = 1; j <= n; ++j) printf("%d ", sum += d[i][j]);
		printf("\n");
	}
	return 0;
}