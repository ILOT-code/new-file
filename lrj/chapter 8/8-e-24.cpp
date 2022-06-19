#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1005;
int l, r, left[maxn / 2], right[maxn / 2];

int main() {
	while (~scanf("%d%d", &l, &r) && l && r) {
		int L = 0, R = 0, idL, idR, ans;
		for (int i = l; i <= r; i += 2) {
			if (i < 0) {
				scanf("%d", &left[(-i) / 2]);
				if (L <= left[(-i) / 2]) {L = left[(-i) / 2]; idL = (-i) / 2;}
			} else {
				scanf("%d", &right[i / 2]);
				if (R < right[i / 2]) {R = right[i / 2]; idR = i / 2;}
			}
		}

		l = (-l) / 2; r = r / 2;
		int k = 0, t = 0, temp;
		if (L == R) {
			temp = left[l];
			for (int i = l; i > idL; --i) {
				k += temp; temp = max(temp, left[i - 1]);
			}
			temp = right[r];
			for (int i = r; i > idR; --i) {
				t += temp; temp = max(temp, right[i - 1]);
			}
			ans = min(k, t) * 2 * 2 + (idR + idL + 1) * 2 * L;
		} else {
			int T = min(R, L), p = 0, q = 0;
			while (p < l && left[p] < T) p++;
			while (q < r && right[q] < T) q++;
			if (L < R) {
				for (int i = q; right[i] <= T; ++i) k += right[q];
				temp = left[l];
				for (int i = l; i > p; --i) {
					t += temp; temp = max(temp, left[i - 1]);
				}
			} else {
				for (int i = p; left[i] <= T; ++i) k += left[p];
				temp = right[r];
				for (int i = r; i > q; --i) {
					t += temp; temp = max(temp, right[i - 1]);
				}
			}
			ans = (p + q + 1) * T * 2 + (t + min(k, t)) * 2;
		}
		printf("%d\n", ans);
	}
	return 0;
}