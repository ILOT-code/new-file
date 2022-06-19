//感觉可以不用set,记录下每个雨季旱季的起始与终止时间，把复杂度降为O(n),但实现起来比较复杂。
#include<cstdio>
#include<cstring>
#include<set>
using namespace std;

const int maxn = 1000000 + 10;
int n, m, ans[maxn], full[maxn];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		memset(full, 0, sizeof(full));
		memset(ans, 0, sizeof(ans));
		set<int> dry;
		scanf("%d%d", &n, &m);
		int k, flag = 1;
		for (int i = 0; i < m; ++i) {
			scanf("%d", &k);
			if (!flag) continue;
			if (!k) dry.insert(i);
			else {
				ans[i] = -1;
				set<int>::iterator it = dry.lower_bound(full[k]);
				if (it == dry.end()) flag = 0;
				else{
					ans[*it] = k;
					full[k] = i;
					dry.erase(*it);
				}
			}
		}
		if (!flag) {printf("NO\n"); continue;}
		printf("YES\n");
		for (int i = 0; i < m; ++i) {
			if (i == 0) printf("%d", ans[i]);
			else if (ans[i] >= 0) printf(" %d", ans[i]);
		}
		printf("\n");
	}
	return 0;
}