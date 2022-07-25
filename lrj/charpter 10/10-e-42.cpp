#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;

int T, n, m, A, B;
void update(LL &cnt, int area, int c) {if (A <= area && area <= B) cnt += c;}

int equa(int left, int right, int k) {
	if (left > right) return 0;
	left = (int)ceil(left / (double)k);
	right = (int)floor(right / (double)k);
	return right - left + 1;
}

LL cal(int r, int c) {
	LL cnt = 0;
	int area = r * c;
	update(cnt, area, 4); update(cnt, area, 2 * (r - 1) + 2 * (c - 1));
	cnt += 4 * equa(max(A, r), min(B, area - r), r);
	cnt += 4 * equa(max(A, c), min(B, area - c), c);
	for (int i = 1; i < r; ++i) cnt += 4 * equa(max(r, area - B - c * i), min(area - r, area - A - c * i), r);
	for (int i = 1; i < c; ++i) cnt += 4 * equa(max(i, area - B), min(i * r - i, area - A), i);
	return cnt;
}

LL solve() {
	LL cnt = 0;
	for (int r = 1; r <= n; ++r)
		for (int c = 1; c <= m; ++c)
			cnt += cal(r, c) * (n - r + 1) * (m - c + 1);
	return cnt;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d", &n, &m, &A, &B);
		A *= 2; B *= 2;
		printf("%lld\n", solve());
	}
	return 0;
}
