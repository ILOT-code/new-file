#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 22;
struct Node {
	int sum, state;
} spre[590410], slat[59049 + 10];
int n, a[maxn], cnt1, cnt2;
bool vis[1 << maxn];
bool cmp1(Node a, Node b) {return a.sum < b.sum;}
bool cmp2(Node a, Node b) {return a.sum > b.sum;}

void dfs(int p, int e, int state, int sum, Node* s, int& cnt) {
	if (p > e) {s[++cnt].sum = sum; s[cnt].state = state; return;}
	dfs(p + 1, e, state, sum, s, cnt);
	dfs(p + 1, e, state + (1 << (p - 1)), sum + a[p], s, cnt);
	dfs(p + 1, e, state + (1 << (p - 1)), sum - a[p], s, cnt);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	int mid = (1 + n) >> 1;
	dfs(1, mid, 0, 0, spre, cnt1);
	dfs(mid + 1, n, 0, 0, slat, cnt2);
	sort(spre + 1, spre + 1 + cnt1, cmp2);
	sort(slat + 1, slat + 1 + cnt2, cmp1);
	int ans = 0, p1 = 1, p2 = 1, t;
	while (p1 <= cnt1) {
		while (p2 <= cnt2 && spre[p1].sum + slat[p2].sum < 0) p2++;
		t = p2;
		while (t <= cnt2 && spre[p1].sum + slat[t].sum == 0) {
			int state = spre[p1].state | slat[t].state;
			if (!vis[state]) {
				ans++;
				vis[state] = 1;
			}
			t++;
		}
		p1++;
	}
	printf("%d\n", ans - 1);
	return 0;
}