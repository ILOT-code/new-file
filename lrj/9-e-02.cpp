#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 40 + 5;
int n, pail[4][maxn], cnt[maxn], d[maxn][maxn][maxn][maxn], num[4];

int dp(int k) {
	int &ans = d[num[0]][num[1]][num[2]][num[3]];
	if (ans != -1) return ans;
	if (k >= 5) return ans = 0;
	ans = 0;
	for (int i = 0; i < 4; ++i)if (num[i] != n) {
			num[i]++;
			if (cnt[pail[i][num[i]]] == 1) {
				cnt[pail[i][num[i]]] = 0;
				ans = max(ans, 1 + dp(k - 1));
				cnt[pail[i][num[i]]] = 1;
			} else {
				cnt[pail[i][num[i]]] = 1;
				ans = max(ans, dp(k + 1));
				cnt[pail[i][num[i]]] = 0;
			}
			num[i]--;
		}
	return ans;
}

int main() {
	while (scanf("%d", &n) && n) {
		for (int i = 1; i <= n; ++i)
			for (int j = 0; j < 4; ++j) scanf("%d", &pail[j][i]);

		memset(num, 0, sizeof(num));
		memset(cnt, 0, sizeof(cnt));
		memset(d, -1, sizeof(d));
		printf("%d\n", dp(0));
	}
	return 0;
}