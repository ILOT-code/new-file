//为什么堆里面不会用自定义的PII的小于号?
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
#define fi first
#define se second
typedef pair<int, int> PII; // l, r

const int maxn = 200000 + 10;
int h[maxn], n, m;
bool vis[maxn];
char s[maxn];
vector<PII> ans;
priority_queue < PII, vector<PII>, less<PII>> Q;
int cal(PII a) { return abs(h[a.fi] - h[a.se]); }
bool operator<(PII a, PII b) {
	if (cal(a) == cal(b)) return a.fi > b.fi;
	else return cal(a) > cal(b);
}
int main() {
	scanf("%d", &n);
	scanf("%s", s + 1);
	for (int i = 1; i <= n; ++i) m += (s[i] == 'B');
	for (int i = 1; i <= n; ++i) scanf("%d", &h[i]);
	for (int i = 1; i < n; ++i) {
		if (s[i] == s[i + 1]) continue;
		Q.push(PII(i, i + 1));
	}
	printf("%d\n", min(m, n - m));
	while (!Q.empty()) {
		int x = Q.top().fi, y = Q.top().se; Q.pop();
		if (vis[x] || vis[y]) continue;
		printf("%d %d\n", x, y);
		vis[x] = vis[y] = 1;
		while (x > 0 && vis[x]) {--x;}
		while (y <= n && vis[y]) {++y;}
		if (x > 0 && y <= n && s[x] != s[y]) Q.push(PII(x, y));
	}
	return 0;
}