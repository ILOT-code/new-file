//采用一种三进制写法
#include<cstdio>
#include<cstring>
#include<iostream>
#include<sstream>
using namespace std;
const int maxn = 100 + 20 + 5;
const int INF = 1 << 30;
int s, m, n, d[maxn][1 << 17], st[maxn], c[maxn];

int change_st(int ntc, int stc) {
	for (int i = 0; i < s * 2; i += 2)
		if ((1 << i) & ntc) {
			if ((1 << (i + 1)) & stc) {stc ^= 1 << (i + 1); continue;}
			if ((1 << i) & stc) {stc ^= 1 << i; continue;}
		}
	return stc;
}
int dp(int i, int stc) {
	int &ans = d[i][stc];
	if (ans >= 0) return ans;
	if (i == n + m) return ans = stc == 0 ? 0 : INF;
	ans = INF;
	if (i >= m) ans = dp(i + 1, stc);
	ans = min(ans, c[i] + dp(i + 1, change_st(st[i], stc)));
	return ans;
}

int main() {
	int x;
	string line;
	while (~scanf("%d%d%d", &s, &m, &n) && s) {
		getchar();
		for (int i = 0; i < m + n; i++) {
			getline(cin, line);
			stringstream ss(line);
			ss >> c[i];
			st[i] = 0;
			while (ss >> x) st[i] |= (1 << (2 * x - 2));
		}
		memset(d, -1, sizeof(d));
		printf("%d\n", dp(0, (1 << (2 * s)) - 1));
	}
	return 0;
}