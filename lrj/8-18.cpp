#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 1000000 + 5;
int p[maxn], s[maxn], h[maxn];

int main() {
	int T, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d", &p[i]);
		for (int i = 0; i < n; i++) scanf("%d", &s[i]);
		int level = s[0], ans = 0;
		for (int i = 0; i < n; ++i) {
			if (level > s[i]) level = s[i];
			if (level < p[i]) level = p[i];
			h[i] = level;
		}
		level = s[n - 1];
		for (int i = n - 1; i >= 0; --i) {
			if (level > s[i]) level = s[i];
			if (level < p[i]) level = p[i];
			ans += min(h[i], level) - p[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}
