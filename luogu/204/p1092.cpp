//TLE
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 30;
int n, tr[400];
char a[3][maxn];
bool vis[maxn];

bool dfs(int d, int f, int v) {
	if (d == 0) {
		if (v == 0) return true;
		return false;
	}
	if (f == 0 || f == 1) {
		if (tr[a[f][d]] != -1) return dfs(d, f + 1, v);
		for (int i = 0; i < n; ++i) {
			if (vis[i]) continue;
			vis[i] = 1; tr[a[f][d]] = i;
			if (dfs(d, f + 1, v)) return true;
			vis[i] = 0; tr[a[f][d]] = -1;
		}
		return false;
	}

	if (f == 2) {
		int sum = (tr[a[0][d]] + tr[a[1][d]] + v) % n, nexv = (tr[a[0][d]] + tr[a[1][d]] + v) / n;
		if (tr[a[f][d]] != -1) {
			if (sum == tr[a[f][d]]) return dfs(d - 1, 0, nexv);
			else return false;
		}
		if (vis[sum]) return false;
		vis[sum] = 1; tr[a[f][d]] = sum;
		if (dfs(d - 1, 0, nexv)) return true;
		vis[sum] = 0; tr[a[f][d]] = -1;
		return false;
	}
	return false;
}

int main() {
	memset(tr, -1, sizeof(tr));
	scanf("%d", &n);
	scanf("%s%s%s", a[0] + 1, a[1] + 1, a[2] + 1);
	dfs(n, 0, 0);
	for (int i = 0; i < n; ++i)
		printf("%d ", tr['A' + i]);
	return 0;

}