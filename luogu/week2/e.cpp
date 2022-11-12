#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int mod = 5201314;
long long n, m;

long long cal(long long x) {
	return ((1 + x) * x / 2) % mod;
}
int main() {
	scanf("%lld%lld", &n, &m);
	printf("%lld", (cal(n)*cal(m)) % mod);
}