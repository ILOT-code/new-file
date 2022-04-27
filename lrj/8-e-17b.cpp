//尺取法
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000005;
int n, m, k, a[maxn], vis[105];

int main(){
	int T, kase = 0;
	scanf("%d", &T);
	while(T--){
		scanf("%d %d %d", &n, &m, &k);
		for (int i = 1; i <= 3; ++i) a[i] = i;
		for (int i = 4; i <= n; ++i) a[i] = (a[i - 1] + a[i - 2] + a[i - 3]) % m + 1;
		memset(vis, 0, sizeof(vis));
		int num = 0, L = 1, ans = n + 1;
		for (int i = 1; i <= n; i++) {
		    if (a[i] <= k) {
		        vis[a[i]]++;
		        if (vis[a[i]] == 1) num++;
		    }
		    while (L < i && (a[L] > k || vis[a[L]] > 1)) {
		        if (a[L] <= k)vis[a[L]]--; L++;
		    }
		    if (num == k) ans = min(ans, i - L + 1);
		}
		if(ans <= n) printf("Case %d: %d\n", ++kase, ans);
		else printf("Case %d: sequence nai\n", ++kase);
	}
	return 0;
}