#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<sstream>
#include<algorithm>
using namespace std;

const int maxn = 200 + 5;
const int INF = 1 << 30;

struct Edge {
	int u, v, d;
	Edge(int u = 0, int v = 0, int d = 0): u(u), v(v), d(d) {}
};

vector<Edge> edges[maxn];
int n, root, maxlen, f[maxn], g[maxn], have_father[maxn];

struct UndirectedSon {
	int w, f, g;
	UndirectedSon(int w = 0, int f = 0, int g = 0): w(w), f(f), g(g) {}
};

bool cmp_f(const UndirectedSon& w1, const UndirectedSon& w2) {
	return w1.f < w2.f;
}

bool cmp_g(const UndirectedSon& w1, const UndirectedSon& w2) {
	return w1.g < w2.g;
}
int dfs(int u) {
	int ans = 0;
	for (int i = 0; i < edges[u].size(); ++i) {
		int v = edges[u][i].v;
		if (edges[u][i].d == 1) ans = max(ans, 1 + dfs(v));
	}
	return ans;

}
bool read_data() {
	bool have_data = false;
	n = 0;
	int a, b;
	char dir;
	for (int i = 0; i < maxn; ++i) edges[i].clear();
	memset(have_father, 0, sizeof(have_father));

	while (cin >> a && a) {
		have_data = true;
		if (a > n) n = a;
		string str;
		while (cin >> str && str != "0") {
			int len = str.length();
			dir = str[len - 1];
			stringstream ss(str);
			ss >> b;
			have_father[b] = 1;
			if (b > n) n = b;
			if (dir == 'd') {
				edges[a].push_back(Edge(a, b, 1));
				edges[b].push_back(Edge(b, a, 2));
			} else if (dir == 'u') {
				edges[a].push_back(Edge(a, b, 2));
				edges[b].push_back(Edge(b, a, 1));
			} else {
				edges[a].push_back(Edge(a, b, 0));
				edges[b].push_back(Edge(b, a, 0));
			}
		}
	}
	if (have_data)
		for (int i = 1; i <= n; ++i)
			if (!have_father[i]) {root = i; break;}
	return have_data;
}

void dp(int i, int fa) {
	if (edges[i].empty()) {
		f[i] = g[i] = 0;
		return;
	}
	int f0 = 0, g0 = 0;
	vector<UndirectedSon> sons;
	for (int k = 0; k < edges[i].size(); ++k) {
		int v = edges[i][k].v;
		int d = edges[i][k].d;
		if (v == fa) continue;
		dp(v, i);
		if (d == 0) sons.push_back(UndirectedSon(v, f[v], g[v]));
		else if (d == 1) f0 = max(f0, 1 + f[v]);
		else g0 = max(g0, 1 + g[v]);
	}
	if (sons.empty()) {
		f[i] = f0, g[i] = g0;
		if (f0 + g0 > maxlen) f[i] = g[i] = INF;
		return;
	}
	f[i] = g[i] = INF;
	int s = sons.size();
	sort(sons.begin(), sons.end(), cmp_f);
	int maxg[maxn];
	maxg[s - 1] = sons[s - 1].g;
	for (int j = s - 2; j >= 0; --j) maxg[j] = max(maxg[j + 1], sons[j].g);
	for (int p = 0; p <= s; ++p) {
		int ff = f0, gg = g0;
		if (p > 0) ff = max(ff, sons[p - 1].f + 1);
		if (p < s) gg = max(gg, maxg[p] + 1);
		if (ff + gg <= maxlen) f[i] = min(f[i], ff);
	}

	sort(sons.begin(), sons.end(), cmp_g);
	int maxf[maxn];
	maxf[s - 1] = sons[s - 1].f;
	for (int j = s - 2; j >= 0; --j) maxf[j] = max(maxf[j + 1], sons[j].f);
	for (int p = 0; p <= s; p++) {
		int ff = f0, gg = g0;
		if (p > 0) gg = max(gg, sons[p - 1].g + 1);
		if (p < s) ff = max(ff, maxf[p] + 1);
		if (ff + gg <= maxlen) g[i] = min(g[i], gg);
	}
}

int main() {
	while (read_data()) {
		maxlen = 0;
		for (int i = 1; i <= n; ++i) maxlen = max(maxlen, dfs(i));
		dp(root,-1);
		if (f[root] < INF) cout << maxlen + 1 << "\n";
		else cout << maxlen + 2 << "\n";
	}
	return 0;
}