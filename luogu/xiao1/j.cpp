#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

long long T, n, m;
int main() {
	scanf("%lld", &T);
	while (T--) {
		scanf("%lld%lld", &n, &m);
		if (n == m + 1) printf("Jia\n");
		else if (n % (m + 1) == 0) printf("Jia\n");
		else printf("Zhen\n");
	}
	return 0;
}