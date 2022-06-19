//f[i]如果是INF的话，意味着以i为根的树无论怎么变换。最长链都大于设定值.
//设i的子节点w,如果有f[w]=INF,则必然失败。
//如果f[w]全部合理，则以i为根的树中，可能出现的大于设定值的最长链一定要经过i。
//Undirectedson(Uds)中储存的是i的所有无向边连接的孩子,设有n个。
//对它们需要枚举无向边的各种方向的选取，为2^n.
//但是，可以按照f[i]的大小把它们排序。f[i]的选取只有max(f0,Uds[k]+1),(k取0~n-1)n种可能。
//设f[i]=max(f0,Uds[k]+1)已经选定，则g[i]越小越好。
//g[i]=max(g0,Uds[k'(k'>k)]+1,Uds[k''(k''<k)]+1),此时k'是一定且全部都会存在的，则最好的情况就是让k''消失。
//于是就能求出此时g[i]的最小值。并在线性时间内枚举完毕全部可能。
//于是有了下面的dp.
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

bool dp(int i, int fa) {
	if (edges[i].empty()) {
		f[i] = g[i] = 0;
		return true;
	}
	int f0 = 0, g0 = 0;
	vector<UndirectedSon> sons;
	for (int k = 0; k < edges[i].size(); ++k) {
		int v = edges[i][k].v;
		int d = edges[i][k].d;
		if (v == fa) continue;
		if (!dp(v, i)) return false;
		if (d == 0) sons.push_back(UndirectedSon(v, f[v], g[v]));
		else if (d == 1) f0 = max(f0, 1 + f[v]);
		else g0 = max(g0, 1 + g[v]);
	}
	if (sons.empty()) {
		f[i] = f0, g[i] = g0;
		if (f0 + g0 > maxlen) f[i] = g[i] = INF;
		return f[i] < INF;
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
		if (ff + gg <= maxlen) {f[i] = min(f[i], ff); break;}
	}

	sort(sons.begin(), sons.end(), cmp_g);
	int maxf[maxn];
	maxf[s - 1] = sons[s - 1].f;
	for (int j = s - 2; j >= 0; --j) maxf[j] = max(maxf[j + 1], sons[j].f);
	for (int p = 0; p <= s; p++) {
		int ff = f0, gg = g0;
		if (p > 0) gg = max(gg, sons[p - 1].g + 1);
		if (p < s) ff = max(ff, maxf[p] + 1);
		if (ff + gg <= maxlen) {g[i] = min(g[i], gg); break;}
	}
	return f[i] < INF;
}

int main() {
	while (read_data()) {
		maxlen = 0;
		for (int i = 1; i <= n; ++i) maxlen = max(maxlen, dfs(i));
		if (dp(root, -1)) cout << maxlen + 1 << "\n";
		else cout << maxlen + 2 << "\n";
	}
	return 0;
}