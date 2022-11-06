#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 500000 + 10;
int n, a[maxn];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);

	int ans = 0, start = 1;
	while (1) {
		int nex = upper_bound(a + start, a + 1 + n, ans) - a;
		if (nex <= n) ans++, start = nex + 1;
		else break;
	}
	printf("%d\n", ans);
	return 0;
}