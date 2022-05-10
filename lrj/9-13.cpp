//d[maxn][2]数组不开也可以。
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

const int maxn = 200 + 5;
int n, cnt, d[maxn][2], f[maxn][2];
vector<int> sons[maxn];
map<string, int> dict;

int ID(const string &s) {
	if (!dict.count(s)) dict[s] = cnt++;
	return dict[s];
}

int dp(int u, int k) {
	f[u][k] = 1; d[u][k] = k;
	for (int i = 0; i < sons[u].size(); ++i) {
		int v = sons[u][i];
		if (k == 1) {
			d[u][k] +=  dp(v, 0);
			if (!f[v][0]) f[u][k] = 0;
		} else {
			d[u][k] += max(dp(v, 1), dp(v, 0));
			if (d[v][1] == d[v][0]) f[u][k] = 0;
			if (d[v][0] > d[v][1] && !f[v][0]) f[u][k] = 0;
			if (d[v][1] > d[v][0] && !f[v][1]) f[u][k] = 0;
		}
	}
	return d[u][k];
}

int main() {
	string s1, s2;
	while ((cin >> n >> s1) && n) {
		cnt = 0; dict.clear();
		for (int i = 0; i < n; ++i) sons[i].clear();
		ID(s1);
		for (int i = 0; i < n - 1; ++i) {
			cin >> s1 >> s2;
			sons[ID(s2)].push_back(ID(s1));
		}
		printf("%d ", max(dp(0, 0), dp(0, 1)));
		bool unique = false;
		if(d[0][0] > d[0][1] && f[0][0]) unique = true;
		if(d[0][1] > d[0][0] && f[0][1]) unique = true;
		if(unique) printf("Yes\n"); else printf("No\n");
	}
	return 0;
}