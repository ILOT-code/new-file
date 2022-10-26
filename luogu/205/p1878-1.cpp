#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 200000 + 10;
int h[maxn], n, m;
bool vis[maxn];
char s[maxn];
struct Node {
	int x, y;
	Node(int x = 0, int y = 0): x(x), y(y) {}
	bool operator<(const Node& rhs) const {
		int a = abs(h[x] - h[y]), b = abs(h[rhs.x] - h[rhs.y]);
		if (a == b) return x > rhs.x;
		else return a > b;
	}
};
vector<Node> ans;
priority_queue <Node, vector<Node>, less<Node>> Q;
int main() {
	scanf("%d", &n);
	scanf("%s", s + 1);
	for (int i = 1; i <= n; ++i) m += (s[i] == 'B');
	for (int i = 1; i <= n; ++i) scanf("%d", &h[i]);
	for (int i = 1; i < n; ++i) {
		if (s[i] == s[i + 1]) continue;
		Q.push(Node(i, i + 1));
	}
	printf("%d\n", min(m, n - m));
	while (!Q.empty()) {
		int x = Q.top().x, y = Q.top().y; Q.pop();
		if (vis[x] || vis[y]) continue;
		printf("%d %d\n", x, y);
		vis[x] = vis[y] = 1;
		while (x > 0 && vis[x]) {--x;}
		while (y <= n && vis[y]) {++y;}
		if (x > 0 && y <= n && s[x] != s[y]) Q.push(Node(x, y));
	}
	return 0;
}