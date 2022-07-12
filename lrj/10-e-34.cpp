#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;

int T, kase, l, r, lef[22], rig[22];
ull A, B, f[22][22][3][3][3][3];
bool vis[22][22][3][3][3][3];

ull dfs(int rev, int ori, int rl, int rr, int ol, int orr) {
	if (vis[rev][ori][rl][rr][ol][orr]) return f[rev][ori][rl][rr][ol][orr];
	vis[rev][ori][rl][rr][ol][orr] = true;
	ull &now = f[rev][ori][rl][rr][ol][orr]; now = 0;
	if (!rev) {
		if (ori == r + 1) return now = ((ol != 0) && (orr != 2));
		if (ori > l) return now = (ol != 0);
		else return now = 0;
	}
	for (int i = max(rev == 1 ? 1 : 0, rl == 2 ? 0 : lef[rev]); i <= (rr == 0 ? 9 : rig[rev]); i++)
		now += dfs(rev - 1, ori + 1,
		          (i == lef[rev] ? rl : 2), (i == rig[rev]) ? rr : 0,
		           i == lef[ori] ? ol : (i < lef[ori] ? 0 : 2), i == rig[ori] ? orr : (i < rig[ori] ? 0 : 2));
	return now;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%llu%llu", &A, &B);
		memset(vis, 0, sizeof(vis));
		l = r = 0;
		memset(lef, 0, sizeof(lef)); memset(rig, 0, sizeof(rig));
		while (A) {lef[++l] = A % 10; A /= 10;}
		while (B) {rig[++r] = B % 10; B /= 10;}
		ull ans = dfs(r, 1, 1, 1, 1, 1);
		for (int i = r - 1; i >= l; i--) ans += dfs(i, 1, 1, 0, 1, 1);
		printf("Case %d: %llu\n", ++kase, ans);
	}
	return 0;
}