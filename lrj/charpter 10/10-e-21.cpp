#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;

struct P {
	LL k, n;
	bool operator<(const P& rhs) {
		return n == rhs.n ? k < rhs.k : n < rhs.n;
	}
	P(LL k = 0, LL n = 0): k(k), n(n) {}
};
vector<P> p;

LL m;
LL C(LL k, LL n) {
	LL ans = 1;
	for (int i = 1; i <= k; ++i) {
		if (ans / i > m / (n - i + 1)) return m + 1;
		ans *= (n - i + 1);
		ans /= i;
	}
	return ans;
}

void solve() {
	p.clear();
	for (LL k = 1; C(k, 2 * k) <= m; ++k) {
		LL left = 2 * k, right = m;
		while (left < right) {
			LL mid = (right + left) / 2;
			if (C(k, mid) >= m) right = mid;
			else left = mid + 1;
		}
		if (C(k, left) != m) continue;
		p.push_back(P(k, left));
		if (left != 2 * k) p.push_back(P(left - k, left));
	}
	sort(p.begin(), p.end());
	int len = p.size();
	printf("%d\n", len);
	for (int i = 0; i < len; ++i) printf("(%lld,%lld)%c", p[i].n, p[i].k, i == len - 1 ? '\n' : ' ');
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%lld", &m);
		solve();
	}
	return 0;
}