#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 100000;
int a[maxn], flag[maxn], next[maxn];
int n, s;

bool solve(int k) {
	int i = 1;
	for (; i <= k; ++i)
		if (next[i] && next[i] <= k)  return false;
	int end = i + s - 1;
	for (; i <= n; ++i) {
		if (i > end) end = i + s - 1;
		if (next[i] && next[i] <= end) return false;
	}
	return true;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &s, &n);
		memset(flag, 0, sizeof(flag));
		memset(next, 0, sizeof(next));
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			if (flag[a[i]]) next[flag[a[i]]] = i;
			flag[a[i]] = i;
		}
		int ans = 0;
		for (int i = 0; i < s; ++i)
			if (solve(i)) ans++;
		printf("%d", ans);
		printf("\n");
	}
	return 0;
}



