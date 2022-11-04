#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n, m, sum, deep, len, h[70], nex[70];
bool vis[70];
bool cmp(int x, int y) {return x > y;}

int getpos(int L, int R, int v) {
	while (L < R) {
		int mid = (L + R) >> 1;
		if (h[mid] > v) L = mid + 1;
		else R = mid;
	}
	return L;
}

bool dfs(int d, int last, int rest) {
	if (d == deep + 1) return true;
	int select;
	if (rest == 0) {
		for (select = 1; select <= n; ++select) if (!vis[select]) break;
		vis[select] = 1;
		bool t = dfs(d + 1, select, len - h[select]);
		vis[select] = 0;
		return t;
	}
	for (select = getpos(last + 1, n + 1, rest); select <= n; select++) {
		if (vis[select]) continue;
		vis[select] = 1;
		int  t = dfs(d, select, rest - h[select]);
		vis[select] = 0;
		if (t) return true;
		if (rest == len || rest == h[select]) return false;
		select = nex[select];
	}
	return false;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &h[i]), sum += h[i], m = max(m, h[i]);
	sort(h + 1, h + 1 + n, cmp);
	nex[n] = n;
	for (int i = n - 1; i >= 1; --i) {
		if (h[i] == h[i + 1]) nex[i] = nex[i + 1];
		else nex[i] = i;
	}
	bool flag = 0;
	for (len = m; len <= sum / 2; ++len) {
		if (sum % len) continue;
		deep = sum / len;
		if (dfs(1, 0, len)) {flag = 1; break;}
	}
	if (!flag) printf("%d\n", sum);
	else printf("%d\n", len);
	return 0;
}