#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n, a[70 + 5];

int cal(int d, int x) {
	int ret = 0, need = a[x];
	need = a[x] + d;
	for (int i = x + 1; i <= n; ++i, need += d) {
		if (a[i] == need) continue;
		else ret++;
	}
	need = a[x] - d;
	for (int i = x - 1; i >= 1; --i, need -= d) {
		if (a[i] == need) continue;
		else ret++;
	}
	return ret;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	int ans = 0x3f3f3f3f;
	for (int d = -(200 / (n - 1)); d <= (200 / (n - 1)); ++d)
		for (int i = 1; i <= n; ++i)
			ans = min(ans, cal(d, i));
	printf("%d\n", ans);
	return 0;
}