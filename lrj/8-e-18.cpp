#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n, a[maxn], left[maxn], right[maxn], stack[maxn];
long long sum[maxn];
bool first;

void init() {
	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
	memset(stack, 0, sizeof(stack));
	int top = 0;
	for (int i = 1; i <= n; ++i) {
		while (top > 0 && a[stack[top - 1]] >= a[i]) top--;
		left[i] = top == 0 ? 1 : (stack[top - 1] + 1);
		stack[top++] = i;
	}
	top = 0;
	memset(stack, 0, sizeof(stack));
	for (int i = n; i >= 1; i--) {
		while (top > 0 && a[stack[top - 1]] >= a[i]) top--;
		right[i] = top == 0 ? n : (stack[top - 1] - 1);
		stack[top++] = i;
	}
}

void solve() {
	long long  max_v = 0;
	int r = 1, l = 1;
	for (int i = 1; i <= n; ++i) {
		long long  temp_v = (sum[right[i]] - sum[left[i] - 1]) * a[i];
		if (temp_v > max_v || ( temp_v == max_v && (r - l) > (right[i] - left[i]))) {
			max_v = temp_v;
			l = left[i];
			r = right[i];
		}
	}
	if (!first) printf("\n");
	else first = 0;
	printf("%lld\n%d %d\n", max_v, l, r);
}

int main() {
	first = 1;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		init();
		solve();
	}
	return 0;
}