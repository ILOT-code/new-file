#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 5;
char s[maxn];
int n, d[maxn], p[maxn][maxn], vis[maxn][maxn];

int is_palindrome(int i, int j) {
	if (vis[i][j]) return p[i][j];
	vis[i][j] = 1;
	if (i >= j) return p[i][j] = 1;
	if (s[i] !=  s[j]) return p[i][j] = 0;
	return p[i][j] = is_palindrome(i + 1, j - 1);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		memset(vis, 0, sizeof(vis));
		scanf("%s", s + 1);
		n = strlen(s + 1);
		d[0] = 0;
		for (int i = 1; i <= n; i++) {
			d[i] = i;
			for (int j = 0; j < i; j++)
				if (is_palindrome(j + 1, i)) d[i] = min(d[i], d[j] + 1);
		}
		printf("%d\n", d[n]);
	}
}