#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 500 + 5;
int A[maxn], a[maxn], P[maxn], n, flag[maxn];

int solve(int x, int d) {
	memset(flag, 0, sizeof(flag));
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		a[i] = x;
		x = (x + d + n) % n;
	}
	for (int i = 0; i < n; ++i)
		if (!flag[i]) {
			int t = i;
			while (!flag[t]) {
				flag[t] = 1;
				t = P[a[t]];
			}
			cnt++;
		}
	return n - cnt;
}

int main() {
	while (~scanf("%d", &n) && n) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &A[i]);
			P[--A[i]] = i;
		}
		int ans = n;
		for (int i = 0; i < n; ++i) {
			ans = min(ans, solve(i, 1));
			ans = min(ans, solve(i, -1));
		}
		printf("%d\n", ans);
	}
	return 0;
}