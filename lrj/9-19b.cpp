#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

const int maxn = 1000 + 5;

int n, G[maxn][maxn], d[maxn][2 * maxn], color[maxn], diff[maxn], cnt;
vector<int> team[maxn][2];

bool dfs(int u, int c) {
	color[u] = c;
	team[cnt][c].push_back(u);
	for (int v = 0; v < n; ++v)
		if (u != v && !(G[u][v] && G[v][u])) {
			if (color[v] != -1 && color[v] == color[u]) return false;
			if (color[v] == -1 && !dfs(v, !c)) return false;
		}
	return true;
}
bool build_graph() {
	memset(color, -1, sizeof(color));
	cnt = 0;
	for (int i = 0; i < n; ++i)
		if (color[i] == -1) {
			team[cnt][0].clear(); team[cnt][1].clear();
			if (!dfs(i, 0)) return false;
			diff[cnt] = team[cnt][0].size() - team[cnt][1].size();
			cnt++;
		}
	return true;
}

void print_ans(int ans) {
	vector<int> team0, team1;
	for (int i = cnt - 1; i >= 0; i--) {
		int t;
		if (d[i][ans - diff[i] + n]) {t = 0; ans -= diff[i];}
		else {t = 1; ans += diff[i];}
		for (int j = 0; j < team[i][t].size(); j++) team0.push_back(team[i][t][j]);
		for (int j = 0; j < team[i][1 ^ t].size(); j++) team1.push_back(team[i][1 ^ t][j]);
	}
	printf("%d", team0.size());
	for (int i = 0; i < team0.size(); i++) printf(" %d", team0[i] + 1);
	printf("\n");
	printf("%d", team1.size());
	for (int i = 0; i < team1.size(); i++) printf(" %d", team1[i] + 1);
	printf("\n");

}
void dp() {
	memset(d, 0, sizeof(d));
	d[0][0 + n] = 1;
	for (int i = 0; i < cnt; i++)
		for (int j = -n; j <= n; j++) if (d[i][j + n]) {
				d[i + 1][j + diff[i] + n] = 1;
				d[i + 1][j - diff[i] + n] = 1;
			}
	for (int ans = 0; ans <= n; ans++) {
		if (d[cnt][ans + n]) { print_ans(ans); return; }
		if (d[cnt][-ans + n]) { print_ans(-ans); return; }
	}

}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		memset(G, 0, sizeof(G));
		for (int u = 0, v; u < n; u++)
			while (~scanf("%d", &v) && v) G[u][v - 1] = 1;
		if (n == 1 || !build_graph()) printf("No solution\n");
		else dp();
		if (T) printf("\n");
	}
	return 0;
}

