#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 50 + 5;
const int INF = 0x3f3f3f3f;
int d[maxn][maxn];
char s[maxn];

int main() {
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	memset(d, INF, sizeof(d));
	for (int i = 1; i <= n ; ++i) d[i][i] = 1;
	for (int len = 1; len < n; ++len)
		for (int i = 1; i + len <= n; ++i) {
			int j = i + len;
			if (s[i] == s[j]) d[i][j] = min(d[i][j - 1], d[i + 1][j]);
			else
				for (int k = i; k < j; ++k) d[i][j] = min(d[i][j], d[i][k] + d[k + 1][j]);
		}
	printf("%d\n", d[1][n]);
	return 0;
}