#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;

const int maxn = 100000 + 5;
int T, n;
LL a[maxn];

struct Item {
	LL g;
	int p;
	Item(LL g = 0, int p = 0): g(g), p(p) {}
	bool operator<(const Item&rhs)const { return p < rhs.p; }
};
LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);
		vector<Item> now;
		long long ans = 0;
		
		for (int j = 0; j < n; ++j) {
			now.push_back(Item(a[j], j));
			for (int i = 0; i < now.size() - 1; ++i) now[i].g = gcd(now[i].g, a[j]);
			vector<Item> next;
			for (int k = 0; k < now.size(); ++k)
				if (k == 0 || now[k].g != now[k - 1].g) {
					next.push_back(now[k]);
					ans = max(ans, now[k].g * (j - now[k].p + 1));
				}
			now = next;
		}
		printf("%lld\n", ans);
	}
	return 0;
}