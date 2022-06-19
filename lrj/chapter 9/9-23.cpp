#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
#define REP(i,n) for(int i = 0; i < (n); i++)

const int maxn = 16;
int n, overlap[maxn][maxn][2][2], d[1 << maxn][maxn][2], len[maxn];
string s[maxn][2];

struct Item {
	string s, rev;
	bool operator<(const Item &rhs) {
		return s.length() < rhs.s.length();
	}
} temp[maxn];

int calc_overlap(const string &a, const string &b) {
	int n1 = a.length(), n2 = b.length();
	for (int i = 1, j; i < n1; ++i) { //如果n=1,则首尾元素相同，从1开始计算才能得到解（否则得到0).
		if (i + n2 - 1 < n1) continue;
		for (j = 0; j + i < n1; ++j)
			if (a[i + j] != b[j]) break;
		if (j + i == n1) return j;
	}
	return 0;
}

inline void update(int& x, int v) {
	if (x < 0 || v < x) x = v;
}
void solve() {
	memset(d, -1, sizeof(d));
	d[1][0][0] = len[0];
	for (int s = 1; s < (1 << n) - 1; ++s)
		REP(i, n) REP(x, 2) if (d[s][i][x] != -1)
			REP(j, n) if (!(s & (1 << j)))
				REP(y, 2) update(d[s | (1 << j)][j][y], d[s][i][x] + len[j] - overlap[i][j][x][y]);
	int ans = -1;
	REP(i, n) REP(x, 2) if (d[(1 << n) - 1][i][x] != -1)
		update(ans, d[(1 << n) - 1][i][x] - overlap[i][0][x][0]);
	if (ans <= 1) ans = 2;
	printf("%d\n", ans);
}

int main() {
	while (~scanf("%d", &n) && n) {
		REP(i, n) {
			cin >> temp[i].s;
			temp[i].rev = temp[i].s;
			reverse(temp[i].rev.begin(), temp[i].rev.end());
		}
		int tmp_n = 0;
		sort(temp, temp + n);
		REP(i, n) {
			bool need = true;
			for (int j = i + 1; j < n; ++j) {
				if (temp[j].s.find(temp[i].s) != string::npos ||
				        temp[j].rev.find(temp[i].s) != string::npos) {need = false; break;}
			}
			if (need) {
				s[tmp_n][0] = temp[i].s;
				s[tmp_n][1] = temp[i].rev;
				len[tmp_n++] = temp[i].s.length();
			}
		}
		n = tmp_n;
		REP(i, n) REP(j, n) REP(x, 2) REP(y, 2)
			overlap[i][j][x][y] = calc_overlap(s[i][x], s[j][y]);
		solve();
	}
	return 0;
}
