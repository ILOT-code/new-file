#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 5;
const int INF = 0x3f3f3f3f;
char start[maxn], goal[maxn];
int len, kase, d[maxn][12][12][12], vis[maxn][12][12][12];

int dp(int pos, int a, int b, int c) {
	int &ans = d[pos][a][b][c];
	if (vis[pos][a][b][c] == kase) return ans;
	vis[pos][a][b][c] = kase;
	if (pos >= len) return ans = 0;
	ans = INF;
	int temp = goal[pos] - '0', cur = pos + 3 < len ? start[pos + 3] - '0' : 0;
	int step = (temp - a + 10) % 10;
	for (int i = 0; i <= step; ++i)
		for (int j = 0; j <= i; ++j)
			ans = min(ans, dp(pos + 1, (b + i + 10) % 10, (c + j + 10) % 10, cur) + step);

	step = (a - temp + 10) % 10;
	for (int i = 0; i <= step; ++i)
		for (int j = 0; j <= i; ++j)
			ans = min(ans, dp(pos + 1, (b - i + 10) % 10, (c - j + 10) % 10, cur) + step);
	return ans;
}
int main() {
	while (~scanf("%s%s", start, goal)) {
		kase++;
		len = strlen(start);
		int b = 1 < len ? start[1] - '0' : 0, c = 2 < len ? start[2] - '0' : 0;
		printf("%d\n", dp(0, start[0] - '0', b, c));
	}
	return 0;
}