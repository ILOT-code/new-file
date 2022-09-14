#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
const int INF = 0x3f3f3f3f;
int n, A[maxn], d[maxn], g[maxn];

int find(int left, int right, int v) {
	while (left < right) {
		int mid = (left + right) / 2;
		if (g[mid] >= v) left = mid + 1;
		else right = mid;
	}
	return left;
}

int main() {
	while (~scanf("%d", &A[n])) n++;
	for (int i = 1; i <= n; ++i) g[i] = 0;
	int ans1 = 0;
	for (int i = 0; i < n; ++i) {
		int k = find(1, 1 + n, A[i]);
		d[i] = k;
		ans1 = max(ans1, k);
		g[k] = A[i];
	}

	for (int i = 1; i <= n; ++i) g[i] = INF;
	int ans2 = 0;
	for (int i = 0; i < n; ++i) {
		int k = lower_bound(g + 1, g + 1 + n, A[i]) - g;
		d[i] = k;
		ans2 = max(ans2, k);
		g[k] = A[i];
	}
	printf("%d\n%d\n", ans1, ans2);
	return 0;
}