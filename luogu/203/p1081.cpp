#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn = 100000 + 10;
int n, x0, m, pos[maxn], c[2][maxn], f[maxn][20][2];
LL d[2][maxn], s[2][maxn][20][2]; //谁的？ 谁先手？
struct City {
	int p, next, last;
	LL h;
	bool operator<(const City& rhs) {return h < rhs.h;};
} city[maxn];

void update(int i, int p, int x) {
	if (x == 0) return;
	LL nd = abs(city[x].h - city[p].h);
	if (c[0][i] == 0 || nd < d[0][i] || (nd == d[0][i] && city[pos[c[0][i]]].h > city[x].h)) {
		c[1][i] = c[0][i], d[1][i] = d[0][i];
		c[0][i] = city[x].p, d[0][i] = nd;
	}
	else if (c[1][i] == 0 || nd < d[1][i] || (nd == d[1][i] && city[pos[c[1][i]]].h > city[x].h)) {
		c[1][i] = city[x].p, d[1][i] = nd;
	}
}
LL la, lb;
void cal(int st, int x) {
	int p = st;
	la = lb = 0;
	for (int i = 18; i >= 0; --i)
		if (f[p][i][1] && la + lb + s[0][p][i][1] + s[1][p][i][1] <= x) {
			la += s[1][p][i][1];
			lb += s[0][p][i][1];
			p = f[p][i][1];
		}

}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", &city[i].h), city[i].p = i;
	sort(city + 1, city + 1 + n);
	for (int i = 1; i <= n; ++i) {
		pos[city[i].p] = i;
		city[i].last = i - 1;
		city[i].next = i == n ? 0 : i + 1;
	}
	for (int i = 1; i <= n; ++i) {
		int p = pos[i];
		update(i, p, city[p].last); update(i, p, city[city[p].last].last);
		update(i, p, city[p].next); update(i, p, city[city[p].next].next);
		if (city[p].last) city[city[p].last].next = city[p].next;
		if (city[p].next) city[city[p].next].last = city[p].last;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < 2; ++j) {
			f[i][0][j] = c[j][i];
			if (j == 0) { s[0][i][0][j] = d[0][i], s[1][i][0][j] = 0; }
			if (j == 1) { s[1][i][0][j] = d[1][i], s[0][i][0][j] = 0; }
			f[i][1][j] = c[j ^ 1][c[j][i]];
			if (j == 0) {s[0][i][1][j] = d[0][i], s[1][i][1][j] = d[1][c[j][i]];}
			if (j == 1) {s[1][i][1][j] = d[1][i], s[0][i][1][j] = d[0][c[j][i]];}
		}
	for (int j = 2; j <= 18; ++j)
		for (int i = 1; i <= n; ++i)
			for (int k = 0; k < 2; ++k) {
				int t = f[i][j - 1][k];
				f[i][j][k] = f[t][j - 1][k];
				s[0][i][j][k] = s[0][i][j - 1][k] + s[0][t][j - 1][k];
				s[1][i][j][k] = s[1][i][j - 1][k] + s[1][t][j - 1][k];
			}
	scanf("%d", &x0);
	double ans = 2e10;
	int id = 0;
	for (int i = 1; i <= n; ++i) {
		cal(i, x0);
		double newnum;
		if (lb == 0) newnum = 2e10;
		else newnum = (double)la / (double)lb;
		if (id == 0 || newnum < ans || (newnum == ans && city[pos[i]].h > city[pos[id]].h)) {
			ans = newnum;
			id = i;
		}
	}
	printf("%d\n", id);
	scanf("%d", &m);
	for (int i = 1, r, x; i <= m; ++i) {
		scanf("%d%d", &r, &x);
		cal(r, x);
		printf("%lld %lld\n", la, lb);
	}
	return 0;
}