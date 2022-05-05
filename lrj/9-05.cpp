#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 50 + 5;
const int maxt = 180 * maxn + 678;
int d[maxt], T, n;

int main() {
	int KASE, kase = 1;
	scanf("%d", &KASE);
	while (KASE--) {
		scanf("%d%d", &n, &T);
		memset(d, -1, sizeof(d));
		d[0] = 0;
		int t = 0, ans = 0, ans_t = -1;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &t);
			for (int j = T - t ; j >= 0; --j)
				if(d[j] != -1)
					if(d[j + t] < d[j] + 1){
						d[j+t] = d[j] + 1;
						ans = max(ans, d[j] + 1);
					}
		}
		for(int i = T; i >= 0; --i)
			if(d[i] != -1)
				if(d[i] == ans && i != T){
					ans++;
					ans_t = i + 678;
					break;
				}
		if(ans_t == -1)
			for(int i = T; i >= 0; --i)
				if(d[i] != -1)
					if(d[i] == ans - 1){
						ans_t = i + 678;
						break;
					}


		printf("Case %d: %d %d\n", kase++, ans, ans_t);
	}
	return 0;
}