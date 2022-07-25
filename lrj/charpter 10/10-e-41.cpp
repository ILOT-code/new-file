#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int mod = 1 << 16;
int bit[16 + 1], sum[16][1 << 16];
int n, kase, add;
long long ans;

int main() {
	bit[0] = 1 ;
	for (int i = 1 ; i <= 16 ; ++i) bit[i] = bit[i - 1] << 1;
	while (~scanf("%d", &n) && n != -1) {
		memset(sum, 0, sizeof(sum));
		add = 0; ans = 0;
		for (int i = 1, x; i <= n ; ++i) {
			scanf("%d", &x) ;
			for (int j = 0 ; j < 16 ; ++j) sum[j][x % bit[j + 1]]++;
		}
		for (int i = 0 ; i < 16 ; ++i)
			for (int j = 1 ; j < 1 << (i + 1); ++j) sum[i][j] += sum[i][j - 1];

		char s[20];
		while (scanf("%s", s) && s[0] != 'E') {
			int x; scanf("%d", &x) ;
			if (s[0] == 'Q') {
				int rem = add % bit[x] ;
				if (!(add & bit[x])) ans += sum[x][bit[x + 1] - 1 - rem] - sum[x][bit[x] - 1 - rem];
				else ans += sum[x][bit[x] - 1 - rem] + sum[x][bit[x + 1] - 1] - sum[x][bit[x + 1] - 1 - rem];
			}
			else (add += x) %= mod ;
		}
		printf("Case %d: %lld\n", ++kase, ans);
	}
	return 0;
}