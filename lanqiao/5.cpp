#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int mod = 65521;

int n, m, f[100000], d[10];

int main() {
	scanf("%d%d", &n, &m);

	f[0] = f[1] = f[2] = 1;
	for (int i = 3; i <= n; ++i) f[i] = (f[i - 1] + f[i - 3]) % mod;

	int t = n % 3 == 0 ? 1 : 0;

	d[0] = 1, d[1] = t, d[2] = t;
	for (int i = 3; i <= m; ++i) d[i] = ((d[i - 1] + d[i - 2]) * t + d[i - 3] * f[n]) % mod;
	printf("%d %d\n", d[m],f[n]);
	return 0;

}