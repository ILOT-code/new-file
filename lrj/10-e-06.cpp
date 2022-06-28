#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 10;
int n, cnt, p[maxn], vis[maxn];

void init() {
	for (int i = 2; i < maxn; ++i) {
		if (!vis[i]) p[cnt++] = i;
		for (int j = 0; j < cnt && i * p[j] < maxn; ++j) {
			vis[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
}

int main() {
	init();
	while (~scanf("%d", &n) && n) {
		int l = 0, r = 0, sum = 0, ans = 0;
		while (l <= r) {
			if (sum < n) {
				if (p[r] > n) break;
				sum += p[r++];
			}
			else sum -= p[l++];
			if (sum == n) ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}