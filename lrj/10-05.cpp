#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 30000000;
int T, n, kase;
int cnt[maxn + 1], sum[maxn + 1];

void init() {
	for (int c = 1; c <= maxn; ++c)
		for (int a = c * 2; a <= maxn; a += c) {
			int b = a - c;
			if (c == (a ^ b)) cnt[a]++;
		}
	for (int i = 1; i <= maxn; ++i) sum[i] = sum[i - 1] + cnt[i];
}

int main() {
	init();
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		printf("Case %d: %d\n", ++kase, sum[n]);
	}
	return 0;
}