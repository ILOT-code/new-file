#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define fi first
#define se second
typedef pair<int, int> PII;

const int maxn = 100000 + 10;
const int mod = 1e8 - 3;
int n, ans, A[maxn], T[maxn];
PII a[maxn], b[maxn];

void merge_sort(int x, int y) {
	if (y - x > 1) {
		int m = x + (y - x) / 2;
		int p = x, q = m, i = x;
		merge_sort(x, m); merge_sort(m, y);
		while (p < m || q < y) {
			if (q >= y || (p < m && A[p] <= A[q])) T[i++] = A[p++];
			else T[i++] = A[q++], ans = (ans + m - p) % mod;
		}
		for (i = x; i < y; ++i) A[i] = T[i];
	}
}


int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i].fi), a[i].se = i;
	for (int i = 0; i < n; ++i) scanf("%d", &b[i].fi), b[i].se = i;
	sort(a, a + n); sort(b , b + n);
	for (int i = 0; i < n; ++i) A[a[i].se] = b[i].se;
	merge_sort(0, n);
	printf("%d\n", ans);
	return 0;
}