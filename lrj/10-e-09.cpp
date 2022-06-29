#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 35000 + 10;
int T, U, L;
int cnt, vis[maxn + 1], p[maxn + 1];

void init() {
	for (int i = 2; i < maxn; ++i) {
		if (!vis[i]) p[cnt++] = i;
		for (int j = 0; j < cnt && i * p[j] < maxn; ++j) {
			vis[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
}

int cal(int n) {
	int ans = 1;
	for (int i = 0; i < cnt; ++i) {
		if (n % p[i]) continue;
		int res = 0;
		while (n % p[i] == 0) {
			res++;
			n /= p[i];
		}
		ans *= (res + 1);
	}
	return ans;
}

int main() {
	init();
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &U, &L);
		int ans = 0, Max = 0;
		for (int i = U; i <= L; i++) {
			if (Max < cal(i)) {
				ans = i;
				Max = cal(i);
			}
		}
		printf("Between %d and %d, %d has a maximum of %d divisors.\n", U, L, ans, Max);
	}
	return 0;
}