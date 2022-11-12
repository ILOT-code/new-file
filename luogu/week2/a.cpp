#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 5000 + 5;
int n, c[maxn], a[maxn], b[maxn];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &c[i]);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
	for (int i = 0; i < n; ++i) scanf("%d", &b[i]);

	int ans = 0;
	for (int k = 0; k < n; ++k) {
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			if (b[(i + n - k) % n] == c[a[i]] || b[(i + 1 + n - k) % n] == c[a[i]] || b[(i - 1 + n - k) % n] == c[a[i]])
				cnt++;
		}
		ans = max(ans, cnt);
	}
	printf("%d", ans);
	return 0;
}