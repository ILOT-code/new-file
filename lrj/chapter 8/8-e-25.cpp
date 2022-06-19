#include<cstdio>
#include<cstring>

const int maxn = 300 + 10;
bool G[maxn][maxn];
int n, m;

bool judge(){
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j){
			bool ok1 = 0, ok2 = 0;
			for(int k = 0; k < n; ++k){
				if(G[i][k] && G[j][k]) ok1 = 1;
				if(G[i][k] ^ G[j][k]) ok2 = 1;
			}
			if(ok1 && ok2) return true;
		}
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	int t = 0;
	while (T--) {
		scanf("%d%d", &n, &m);
		memset(G, 0, sizeof(G));
		int u, v;
		for(int i = 0; i < m; ++i) {
			scanf("%d%d", &u, &v);
			G[u][v] = 1;
		}
		printf("Case #%d: ", ++t);
		if (judge()) printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}