#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
typedef long long LL;
using namespace std;

int n, x, y;
LL f[35];
char str[6][3];

int get(int n) {
	int ans = 0, fa = -1;
	stack<int> h[3];
	for (int i = n; i >= 1; --i) h[0].push(i);
	while (1) {
		for (int i = 0; i < 6; ++i) {
			int s = str[i][0] - 'A', e = str[i][1] - 'A';
			if (!h[s].empty() && h[s].top() != fa && (h[e].empty() || h[s].top() < h[e].top())) {
				fa = h[s].top();
				h[e].push(fa); h[s].pop();
				ans++;
				break;
			}
		}
		if (h[1].size() == n || h[2].size() == n) return ans;
	}
}

LL solve() {
	for (int i = 1; i <= 3; ++i) f[i] = get(i);
	x = (f[2] - f[3]) / (f[1] - f[2]);
	y = f[2] - x * f[1];
	for (int i = 4; i <= n; ++i) f[i] = x * f[i - 1] + y;
	return f[n];
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < 6; ++i) scanf("%s", str[i]);
		printf("%lld\n", solve());
	}
	return 0;
}