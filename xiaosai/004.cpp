#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxm = 2 * 100000 + 10;
const int maxn = 100000 + 10;
int n, m, a[maxn];

struct Person {
	int x, y;
	bool operator<(const Person &rhs) const {
		return a[x] < a[rhs.x] || (a[x] == a[rhs.x] && a[y] < a[rhs.y]);
	}
} p[maxm];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &p[i].x, &p[i].y);
		if (a[p[i].x] > a[p[i].y]) swap(p[i].x, p[i].y);
	}
	sort(p, p + m);
	bool flag = 1;
	for (int i = 0; i < m; ++i) {
		if (a[p[i].x] == 0 && a[p[i].y] == 0) {
			flag = 0;
			break;
		}
		if (a[p[i].x]) a[p[i].x]--;
		if (a[p[i].y]) a[p[i].y]--;
	}
	if (flag) printf("YES");
	else printf("NO");
	return 0;
}