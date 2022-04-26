#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 100000 + 5;

int main() {
	int n, d;
	char ans[maxn];
	while (scanf("%d%d", &n, &d)) {
		getchar();
		int k = 0;

		for (int i = 0; i < n; ++i) {
			char c = getchar();
			while (k > 0 && c > ans[k] && k > i - d) k--;
			if (k + d < n) ans[++k] = c;
		}

		ans[++k]=0;
		printf("%s\n",ans);
	}
	return 0;
}