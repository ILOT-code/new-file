#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

bool is_prime(int x) {
	if (x == 1) return false;
	for (int i = 2; i * i <= x; ++i) {
		if (x % i == 0) return false;
	}
	return true;
}

bool judge(int x) {
	for (int i = 2; i < x; ++i)
		for (int j = i; j < x; ++j)
			for (int k = j; k < x; ++k)
				if (is_prime(i) && is_prime(j) && is_prime(k) && i + j + k == x)
					return false;
	return true;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int l, r;
		scanf("%d%d", &l, &r);
		int cnt = 0, i = l;
		for (; i <= r; ++i) {
			if (judge(i)) cnt++;
			if (cnt == 3) break;
		}
		if (cnt < 3) printf("No Answer\n");
		else printf("%d\n", i);
	}
	return 0;
}