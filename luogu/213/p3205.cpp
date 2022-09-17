#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 5;
const int mod = 19650827;
int n, a[maxn], f[maxn][maxn][2];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);

	for (int i = 1; i <= n; ++i) f[i][i][0] = 1;
	for (int len = 1; len < n; ++len)
		for (int i = 1; i + len <= n; ++i) {
			int j = i + len;
			if (a[i] < a[i + 1]) f[i][j][0] += f[i + 1][j][0];
			if (a[i] < a[j]) f[i][j][0] += f[i + 1][j][1];
			if (a[j] > a[i]) f[i][j][1] += f[i][j - 1][0];
			if (a[j] > a[j - 1]) f[i][j][1] += f[i][j - 1][1];
			f[i][j][0] %= mod, f[i][j][1] %= mod;
		}

	printf("%d\n", (f[1][n][0] + f[1][n][1]) % mod);

}