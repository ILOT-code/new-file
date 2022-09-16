#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 5000 + 10;
const long long INF = 0x3f3f3f3f3f3f3f3f;
int n, w, s, q[maxn];
long long d[maxn][maxn], a[maxn];

int main() {
	scanf("%d%d%d", &n, & w, &s);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
	memset(d, -0x3f, sizeof(d));
	d[0][0] = 0;
	int head = 0, tail = 0, ready = 0;
	for (int i = 1; i <= n; ++i) {
		head = tail = ready = 0;
		for (int j = 1; j <= w; ++j) {
			int top = min(w, j + s - 1), low = j - 1;
			while (ready <= top) {
				while (head < tail && d[i - 1][q[tail - 1]] <= d[i - 1][ready]) tail--;
				q[tail++] = ready++;
			}
			while (head < tail && q[head] < low) head++;
			d[i][j] = d[i - 1][q[head]] + 1LL * j * a[i];
		}
	}
	long long ans = -INF;
	for (int i = 1; i <= w; ++i) ans = max(ans, d[n][i]);
	printf("%lld\n", ans);
}