#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 50000 + 5;
int T, n;
double p[maxn + 5];

void init() {
	p[1] = 1;
	for (int i = 1; i < maxn; ++i)
		p[i + 1] = p[i] * (2 * i - 1) / (2 * i);
}

int main () {
	init();
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		printf("%.4lf\n", 1 - p[n / 2]);
	}
	return 0;
}