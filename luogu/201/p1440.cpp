#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 2000000 + 5;
int n, m, a[maxn];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);

	int st[maxn], head = 0, tail = 0, ready = 1;
	
	printf("0\n");
	while (ready < n) {
		while (tail > head && a[ready] <= a[st[tail - 1]]) tail--;
		st[tail++] = ready++;
		while (st[head] < ready - m) head++;
		printf("%d\n", a[st[head]]);
	}
	return 0;
}