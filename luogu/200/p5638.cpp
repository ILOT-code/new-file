#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 1000000 + 5;
int n, k;
LL a[maxn], ans;

LL cal() {
	int head = 1, tail = 1, start = 1;
	LL sum = 0, ret = 0;
	while (head <= n - k) {
		while (tail <= head + k - 1) sum += a[tail++];
		while (start < head) sum -= a[start++];
		ret = max(ret, sum);
		head++;
	}
	return ret;
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i < n; ++i) scanf("%lld", &a[i]), ans += a[i];
	ans -= cal();
	printf("%lld\n", ans);
	return 0;
}