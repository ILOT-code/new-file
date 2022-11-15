#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n, m, fa[maxn];
char col[maxn];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }


int main() {
	scanf("%d%d", &n, &m), getchar();
	for (int i = 1; i <= n; ++i) fa[i] = i, scanf("%c", &col[i]);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		if (col[u] == col[v]) fa[find(u)] = find(v);
	}

	for (int i = 1; i <= m; ++i) {
		int a, b; scanf("%d%d", &a, &b), getchar();
		char c; scanf("%c", &c);
		int x = find(a), y = find(b);
		if (x == y && col[x] != c) printf("0");
		else printf("1");
	}
	return 0;
}