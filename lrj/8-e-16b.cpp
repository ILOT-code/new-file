#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

const int maxn = 5000 + 5;
map<int, int> pos;
int T, n, d, ans, a[maxn], st2[maxn][30], st1[maxn][30], Log[maxn];

void to_start() {
	Log[1] = 0;
	for (int i = 2; i <= n + 1; i++) Log[i] = Log[i / 2] + 1;
	for (int i = 1; i <= n; i++) st1[i][0] = st2[i][0] = a[i];
	for (int j = 1; (1 << j) <= n; j++) {
		for (int i = 1; i + (1 << (j - 1)) <= n; i++) {
			st1[i][j] = max(st1[i][j - 1], st1[i + (1 << (j - 1))][j - 1]);
			st2[i][j] = min(st2[i][j - 1], st2[i + (1 << (j - 1))][j - 1]);
		}
	}
}
int ask_max(int l, int r) {
	int k = Log[r - l + 1];
	int mx = max(st1[l][k], st1[r - (1 << k) + 1][k]);
	return mx;
}
int ask_min(int l, int r) {
	int k = Log[r - l + 1];
	int mx = min(st2[l][k], st2[r - (1 << k) + 1][k]);
	return mx;
}

bool judge() {
	to_start();
	for (int i = 1; i <= n; i++) {
		for (int j = i + 3; j <= n; j++) {
			int t1 = ask_max(i, j);
			int t2 = ask_min(i, j);
			if (a[i] > a[j] && pos[t1] > pos[t2]) return 1;
			if (a[i] < a[j] && pos[t1] < pos[t2]) return 1;
		}
	}
	return 0;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			pos[a[i]] = i;
		}
		if (judge()) printf("YES\n");
		else printf("NO\n");
	}
}
