#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 1000 + 5;
const int maxm = 10 + 5;
int s, n, stamp[maxm][maxm], num[maxm], d[maxn], maxv[maxm];

bool bigger(int a, int b) {
	if (num[a] != num[b]) return num[a] > num[b];
	for (int i = num[a] - 1; i >= 0; i--)
		if (stamp[a][i] == stamp[b][i]) continue;
		else if (stamp[a][i] > stamp[b][i]) return true;
		else return false;
	return 0;
}

int main() {
	while (~scanf("%d%d", &s, &n) && s) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &num[i]);
			for (int j = 0; j < num[i]; ++j) scanf("%d", &stamp[i][j]);
		}
		for (int k = 0; k < n; ++k) {
			memset(d, INF, sizeof(d));
			d[0] = 0;
			for (int i = 0; i < num[k]; ++i)
				for (int j = stamp[k][i]; j < maxn; ++j)
					if (d[j - stamp[k][i] != INF])
						d[j] = min(d[j], d[j - stamp[k][i]] + 1);
			for (int i = 0; i < maxn; ++i)
				if (d[i] > s) {
					maxv[k] = i - 1;
					break;
				}
		}
		int ans = -1, sets = 0;
		for (int i = 0; i < n; ++i) {
			if (ans < maxv[i]) {
				ans = maxv[i];
				sets = i;
			}
			else if (ans == maxv[i] && bigger(sets, i)) sets = i;
		}
		printf("max coverage =%4d :", ans);
		for (int i = 0; i < num[sets]; ++i) printf("%3d", stamp[sets][i]);
		printf("\n");
	}
	return 0;
}