#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;
typedef pair<int, int> PII;
const int maxn = 100 + 5;
const int INF = 0x3f3f3f3f;
int d[maxn][maxn], kase;

map<int, int> mp;

int ID(int x) {
	int idx = mp.size();
	if (!mp.count(x)) mp.insert(PII(x, idx));
	return mp[x];
}

void init() {
	mp.clear();
	memset(d, INF, sizeof(d));
	for (int i = 0; i < maxn; ++i) d[i][i] = 0;
}

int main() {
	int x, y;
	while (~scanf("%d%d", &x, &y) && x && y) {
		init();
		int a = ID(x), b = ID(y);
		d[a][b] = 1;
		while (~scanf("%d%d", &x, &y) && x && y) {
			int a = ID(x), b = ID(y);
			d[a][b] = 1;
		}

		int n = mp.size(), cnt = n * (n - 1);
		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

		double ans = 0;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j) {
				if (i == j) continue;
				ans += d[i][j];
			}
		printf("Case %d: average length between pages = %.3lf clicks\n", ++kase, ans / cnt);
	}
	return 0;
}