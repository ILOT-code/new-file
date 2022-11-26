#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 5;
int n, k, c[maxn][11], a[maxn];
int cnt[11];
bool vis[maxn];
struct Point {
	int v, id;
	bool operator<(Point& rhs) { return v > rhs.v; }
} po[11][maxn];
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= k; ++j) {
			scanf("%d", &c[i][j]);
			po[j][i].v = c[i][j];
			po[j][i].id = i;
		}
	}
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= k; ++i) sort(po[i] + 1, po[i] + 1 + n);

	for (int i = 1; i <= n; ++i) {
		while (vis[po[a[i]][cnt[a[i]] + 1].id]) cnt[a[i]]++;
		printf("%d\n", po[a[i]][cnt[a[i]] + 1].v);
		vis[po[a[i]][cnt[a[i]] + 1].id] = 1;
	}
	return 0;
}
