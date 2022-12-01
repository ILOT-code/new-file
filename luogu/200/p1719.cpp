#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 120 + 5;
int n, m[maxn][maxn];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) scanf("%d", &m[i][j]);

	int ans = 0, a[maxn], sum;

	for (int i = 1; i <= n; ++i) {
		memset(a, 0, sizeof(a));
		for (int j = i; j <= n; ++j) {
			for (int k = 1; k <= n; ++k) a[k] += m[j][k];
			sum = 0;
			for (int k = 1; k <= n; ++k) {
				sum += a[k];
				ans = max(ans, sum);
				if (sum < 0) sum = 0;
			}
		}
	}
	printf("%d\n", ans);
	return 0;

}