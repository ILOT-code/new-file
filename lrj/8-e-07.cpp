#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 300 + 5;
const int maxt = 2 * maxn * maxn;
int a[maxn], n, last, start, ans[maxt];

bool success() {
	bool ok = true;
	if (a[start] != 1) return false;
	for (int i = (start + 1) % n; i != start; i = (i + 1) % n)
		if (a[i] != (i - start + n) % n + 1) {
			ok = false;
			break;
		}
	return ok;
}

int main() {
	while (scanf("%d", &n) && n) {
		for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
		last = 0; start = 0;
		while (!success()) {
			if (a[start] > a[(start + 1) % n] && !(a[start] == n && a[(start + 1) % n] == 1)) {
				swap(a[start], a[(start + 1) % n]);
				ans[last++] = 1;
			}
			else {
				ans[last++] = 2;
				start = (start - 1 + n) % n;
			}
		}
		for (int i = last - 1; i >= 0; --i) printf("%d", ans[i]);
		printf("\n");
	}
	return 0;
}