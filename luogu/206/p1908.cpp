#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 500000 + 10;
int n, A[maxn], T[maxn];
long long ans;
void merge_sort(int x, int y) {
	if (y - x > 1) {
		int m = x + (y - x) / 2;
		int p = x, q = m, i = x;
		merge_sort(x, m); merge_sort(m, y);
		while (p < m || q < y) {
			if (q >= y || (p < m && A[p] <= A[q])) T[i++] = A[p++];
			else T[i++] = A[q++], ans += 1ll * (m - p);
		}
		for (i = x; i < y; ++i) A[i] = T[i];
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", &A[i]);
	merge_sort(0, n);
	printf("%lld\n", ans);
	return 0;
}