#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int mod = 10001;
const int maxn = 100 * 2 + 5;
int T, x[maxn];

void solve() {
	for (int a = 0; a < mod; ++a)
		for (int b = 0; b < mod; ++b) {
			bool ok = true;
			for (int i = 2; i <= 2 * T; i += 2) {
				x[i] = (a * x[i - 1] + b) % mod;
				if (i + 1 <= 2 * T && x[i + 1] != (a * x[i] + b) % mod) {ok = false; break;}
			}
			if (ok) return;
		}
}

int main() {
	scanf("%d", &T);
	for (int i = 1; i < 2 * T; i += 2) scanf("%d", &x[i]);
	solve();
	for (int i = 2; i <= 2 * T; i += 2) printf("%d\n", x[i]);
	return 0;
}