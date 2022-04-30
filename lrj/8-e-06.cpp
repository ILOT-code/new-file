#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 5;
int a[maxn], n, ans, str[4 * maxn];

void sswap(int left, int right) {
	int mid = (left + right - 1) / 2;
	int len = (right - left + 1) / 2;
	str[2 * ans] = left; str[2 * (ans++) + 1] = right;
	for (int i = left; i <= mid; ++i) swap(a[i], a[i + len]);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		ans = 0;
		for (int i = 1; i <= n; ++i) {
			if (a[i] == i) continue;
			int pos = i + 1;
			while (a[pos] != i) pos++;
			if (2 * pos - i - 1 <= n) sswap(i, 2 * pos - i - 1);
			else {
				int c = (pos - i) & 1;
				sswap(i + 1 + c, pos);
				sswap(i, pos - !c);
			}
		}
		printf("%d\n", ans);
		for (int i = 0; i < 2 * ans - 1; i = i + 2) printf("%d %d\n", str[i], str[i + 1]);
	}
	return 0;
}