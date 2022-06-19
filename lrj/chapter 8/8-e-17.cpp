//二分法
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 1e6 + 5;
const int maxk = 100 + 5;
int n, m, k, a[maxn], vis[maxk];

bool judge(int L) {
	int cnt = 0, start = 1;
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; ++i) {
		if (i - start + 1 > L) {
			if (a[start] <= k && vis[a[start]]-- == 1) cnt--;
			start++;
		}
		if (a[i] <= k && vis[a[i]]++ == 0) cnt++;
		if (cnt == k) return true;
	}
	return false;
}

int main() {
	int T , kase = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &k);
		a[1] = 1; a[2] = 2; a[3] = 3;
		for (int i = 4; i <= n; ++i) a[i] = (a[i - 1] + a[i - 2] + a[i - 3]) % m + 1;

		int L = 1, R = n + 1;
		while (L < R) {
			int mid = L + (R - L) / 2;
			if (judge(mid)) R = mid;
			else L = mid + 1;
		}
		if (L <= n) printf("Case %d: %d\n", ++kase, L);
		else printf("Case %d: sequence nai\n", ++kase);
	}
	return 0;
}
