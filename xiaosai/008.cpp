#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000000 + 10;
int n, a[maxn];
long long int d[maxn];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	d[1] = a[1];
	for (int i = 2; i <= n; ++i) {
		if (a[i] >= 0) d[i] = d[i - 1] + a[i];
		else d[i] = d[i - 1] + i * a[i];
	}
	printf("%lld", d[n]);
	return 0;

}