#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 5;
int L[maxn];

int main() {
	int T, n, m;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) scanf("%d", &L[i]);
		sort(L, L + n);

		int ans = 0, right = n - 1, left = 0;
		while (left < right) {
			if (L[right] + L[left] <= m) {
				left++; right--;
			}
			else right--;
			ans++;
		}
		if (left == right) ans++;

		if (T) printf("%d\n\n", ans);
		else printf("%d\n", ans);
	}
	return 0;
}