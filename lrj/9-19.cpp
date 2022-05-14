//下面的DP有一个很明显的错误，不过我一直没发现。
//但稍微冷静思考下就发现了错误。需要冷静。
#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
using namespace std;

const int maxn = 100 + 5;
int n, G[maxn][maxn], d[maxn], color[maxn], diff[maxn], cnt;
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

void dp() {
	vector<int> team0(team[0][0]), team1(team[0][1]);
	d[0] = diff[0];
	for (int i = 1; i < cnt; ++i) {
		if (abs(d[i - 1] + diff[i]) <= abs(d[i - 1] - diff[i])) {
			d[i] = d[i - 1] + diff[i];
			for (int j = 0; j < team[i][0].size(); ++j) team0.push_back(team[i][0][j]);
			for (int j = 0; j < team[i][1].size(); ++j) team1.push_back(team[i][1][j]);
		} else {
			d[i] = d[i - 1] - diff[i];
			for (int j = 0; j < team[i][0].size(); ++j) team1.push_back(team[i][0][j]);
			for (int j = 0; j < team[i][1].size(); ++j) team0.push_back(team[i][1][j]);
		}
	}
	printf("%d", team0.size());
	for (int i = 0; i < team0.size(); ++i) printf(" %d", team0[i] + 1);
	printf("\n");
	printf("%d", team1.size());
	for (int i = 0; i < team1.size(); ++i) printf(" %d", team1[i] + 1);
	printf("\n");
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

