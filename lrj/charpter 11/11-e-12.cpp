#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000000 + 10;
const int dr[4] = { -1, 0, 1, 0};
const int dc[4] = { 0, 1, 0, -1};
int T, n, m, k;
int query[maxn], ans[maxn];

struct Node {
	int r, c, h;
	Node(int r = 0, int c = 0, int h = 0): r(r), c(c), h(h) {}
	bool operator <(const Node& rhs)const { return h < rhs.h;}
};
vector<Node> nodes;

int p[maxn];
bool vis[maxn];
int find(int x) { return p[x] != x ? p[x] = find(p[x]) : x;}
int ID(int r, int c) { return r * m + c; }
bool check(int r, int c) { return 0 <= r && r < n && 0 <= c && c < m;}

void add(const Node& u, int& sum) {
	sum++;
	vis[ID(u.r, u.c)] = 1;
	for (int i = 0; i < 4; ++i) {
		int nr = u.r + dr[i], nc = u.c + dc[i];
		if (check(nr, nc) && vis[ID(nr, nc)]) {
			int a = find(ID(u.r, u.c)), b = find(ID(nr, nc));
			if (a != b) {
				p[a] = b;
				sum--;
			}
		}
	}
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		nodes.clear();
		for (int i = 0; i < n; ++i)
			for (int j = 0, h; j < m; ++j) {
				scanf("%d", &h);
				nodes.push_back(Node(i, j, h));
			}
		sort(nodes.begin(), nodes.end());
		scanf("%d", &k);
		for (int i = 0; i < k; ++i) scanf("%d", &query[i]);

		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n * m; ++i) p[i] = i;
		int pos = nodes.size() - 1, sum = 0;
		for (int i = k - 1; i >= 0; --i) {
			while (pos >= 0 && nodes[pos].h > query[i])
				add(nodes[pos--], sum);
			ans[i] = sum;
		}
		for (int i = 0; i < k; ++i) printf("%d ", ans[i]);
		printf("\n");
	}
	return 0;
}
