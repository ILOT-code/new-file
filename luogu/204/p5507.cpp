#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
#define fi first
#define se second
typedef pair<int, int> PII;
const int maxn = (1 << 24) + 10;
int ope[15][5], g[maxn], pre[maxn], by[maxn];
bool vis[maxn];
int start, dest = 0;
int h(int x) { //h满足三角不等式，无需考虑结点重复.
	int ret = 0;
	for (int i = 0; i < 12 ; ++i) ret += (4 - ((x >> (2 * i)) & 3)) & 3;
	return ret / 2;
}

void print(int s) {
	if (s == start) return;
	print(pre[s]), printf("%d ", by[s] + 1);
}

int main() {
	for (int i = 0, t; i < 12; ++i) {
		scanf("%d", &t); t -= 1;
		start |= t << (2 * i);
		for (int j = 0; j < 4; ++j) scanf("%d", &t), ope[i][j] = t - 1;
	}
	priority_queue<PII, vector<PII>, greater<PII>> Q;
	Q.push(PII(h(start), start)); vis[start] = 1;
	int cnt = 0;
	while (!Q.empty()) {
		int s = Q.top().se; Q.pop();
		if (s == dest) break;
		for (int i = 0; i < 12; ++i) {
			int os = (s >> (2 * i)) & 3, op = ope[i][os], ops = (s >> (2 * op)) & 3;
			int ds = s ^ (os << (2 * i)) ^ (ops << (2 * op));
			ds = ds ^ (((os + 1) & 3) << (2 * i)) ^ (((ops + 1) & 3) << (2 * op));
			if (vis[ds]) continue;
			g[ds] = g[s] + 1; vis[ds] = 1;
			pre[ds] = s, by[ds] = i;
			Q.push(PII(h(ds) + g[ds], ds));
		}
	}
	printf("%d\n", g[0]);
	print(dest);
	return 0;
}