#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000000 + 10;
int n, m, a[maxn], q[maxn];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
	int ready = 0, head = 0, tail = 0;
	for (int i = m - 1; i < n; ++i) {
		while (ready <= i) {
			while (head < tail && a[q[tail - 1]] >= a[ready]) tail--;
			q[tail++] = ready++;
		}
		while (head < tail && q[head] < i - m + 1) head++;
		printf("%d\n", a[q[head]]);
	}
	return 0;
}