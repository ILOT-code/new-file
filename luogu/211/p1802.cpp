#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;
const int maxn = 1000 + 5;
int n, x;
LL d[maxn];

int main() {
	scanf("%d%d", &n, &x);
	for (int i = 1; i <= n; ++i) {
		int lose, win, use;
		scanf("%d%d%d", &lose, &win, &use);
		for (int j = x; j >= 0; --j) {
			if (j >= use) d[j] = max(d[j] + 1LL * lose, d[j - use] + 1LL * win);
			else d[j] += 1LL * lose;
		}
	}
	printf("%lld\n", 5 * d[x]);
}
