#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 5;
int n, m, c, ma[maxn][maxn], a[maxn];

int main() {
	scanf("%d%d%d", &n, &m, &c);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) scanf("%d", &ma[i][j]);
	int ans = -0x3f3f3f3f, x = 0, y = 0, ready = 1, start = 1;
	for (int i = 1; i <= n - c + 1; ++i) {
		int j = i + c - 1;

		while (ready <= j) {
			for (int k = 1; k <= n; ++k) a[k] += ma[ready][k];
			ready++;
		}
		while (start < i) {
			for (int k = 1; k <= n; ++k) a[k] -= ma[start][k];
			start++;
		}

		int head = 1, tail = 1, sum = 0, sta = 1;
		while (head <= n - c + 1) {
			while (tail <= head + c - 1) sum += a[tail++];
			while (sta < head) sum -= a[sta++];
			if (sum > ans) {
				ans = sum;
				x = i, y = head;
			}
			head++;
		}
	}
	printf("%d %d\n", x, y);
	return 0;
}