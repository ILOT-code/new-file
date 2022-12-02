#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 2000000 + 5;
int n, m, a[maxn];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	int st[maxn], head = 0, tail = 0, front = 1, ready = 1;
	while (front <= n - m + 1) {
		while (ready <= front + m - 1) {
			while (tail > head && a[ready] >= a[st[tail - 1]]) tail--;
			st[tail++] = ready++;
		}
		while (st[head] < front) head++;
		printf("%d\n", a[st[head]]);
		front++;
	}
	return 0;
}