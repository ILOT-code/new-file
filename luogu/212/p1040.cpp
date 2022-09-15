#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 30 + 5;
int n, w[maxn], d[maxn][maxn], root[maxn][maxn];

void print(int left, int right) {
	if (left > right) return;
	int r = root[left][right];
	printf("%d ", r);
	print(left,  r - 1);
	print(r + 1, right);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &w[i]), d[i][i] = w[i], root[i][i] = i;
	for (int len = 1; len < n; ++len)
		for (int i = 1; i < n; ++i) {
			int j = i + len;
			for (int k = i; k <= j; ++k) {
				int tmp = (k > i ? d[i][k - 1] : 1) * (k < j ? d[k + 1][j] : 1) + w[k];
				if (d[i][j] < tmp) {
					d[i][j] = tmp;
					root[i][j] = k;
				}
			}
		}

	printf("%d\n", d[1][n]);
	print(1, n);
	return 0;

}