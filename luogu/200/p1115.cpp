#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n, sum, ans, t;
int main() {
	scanf("%d%d", &n, &t);
	sum = ans = t;
	while (--n) {
		scanf("%d", &t);
		if (sum < 0) sum = 0;
		sum += t;
		ans = max(ans, sum);
	}
	printf("%d\n", ans);
	return 0;
}