#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int a, b, pow10[10], cnt[10];

void init() {
	pow10[0] = 1;
	for (int i = 1; i <= 8; ++i) {
		pow10[i] = 10 * pow10[i - 1];
		cnt[i] = i * pow10[i - 1];
	}
}

int change(int n, int* s) {
	int ct = 1, len = 1, t = n;
	while (t /= 10) len++;
	if (n == 0) s[0] = 0;
	while (n) {
		s[len - ct++] = n % 10;
		n /= 10;
	}
	return len;
}

int f(int d, int n) {
	int s[10];
	int len = change(n, s), ans = 0;
	for (int i = 1; i < len; ++i) {
		if (i == 1) ans++;
		else {
			ans += 9 * cnt[i - 1];
			if (d > 0) ans += pow10[i - 1];
		}
	}
	int pre[10];
	pre[0] = (s[0] == d ? 1 : 0);
	for (int i = 1; i < len; ++i) pre[i] = pre[i - 1] + (s[i] == d ? 1 : 0);

	for (int i = 0; i < len; ++i) {
		int maxd = s[i] - 1, mind = 0;
		if (i == 0 && len > 1) mind = 1;
		for (int j = mind; j <= maxd; ++j) {
			ans += cnt[len - i - 1];
			if (j == d) ans += pow10[len - i - 1];
			if (i > 0) ans += pre[i - 1] * pow10[len - i - 1];
		}
	}
	return ans;
}

int main() {
	init();
	while (~scanf("%d%d", &a, &b) && a && b) {
		if (a > b) swap(a, b);
		for (int d = 0; d < 10; ++d) {
			if (d) printf(" ");
			printf("%d", f(d, b + 1) - f(d, a));
		}
		printf("\n");
	}
	return 0;
}