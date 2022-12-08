#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 20000 + 5;
int n, ans;
struct Tran {
	int p, f;
	bool operator<(const Tran& rhs) const {return p < rhs.p;}
} t[2 * maxn];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &t[2 * i].p), t[2 * i].f = 1;
		scanf("%d", &t[2 * i + 1].p), t[2 * i + 1].f = -1;
	}
	sort(t, t + 2 * n);
	int f = 0, start = 0;
	for (int i = 0; i < 2 * n; ++i) {
		if (f == 0) start = t[i].p;
		else start = t[i - 1].p;
		ans += t[i].p - start;
		f += t[i].f;
	}
	printf("%d\n", ans);
	return 0;
}