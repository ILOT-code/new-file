#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 1000000 + 10;
const LL INF = 1000000000 + 100;
int m, p;
LL a[maxn];

int main() {
	scanf("%d", &m);
	LL ret = 1;
	for (int i = 1; i <= m; ++i) {
		int op; scanf("%d", &op);
		if (op == 1) {
			LL x; scanf("%lld", &x);
			a[p++] = x;
		}
		if (op == 2) {
			printf("%lld\n", a[--p] / ret);
		}
		if (op == 3) {
			LL x; scanf("%lld", &x);
			ret *= x;
			if (ret > INF) ret = INF;
		}
	}
	return 0;
}