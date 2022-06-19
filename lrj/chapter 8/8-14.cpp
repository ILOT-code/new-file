#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxm = 200000 + 5;
int n, m;

struct Gate {
	int a, b, out;
} gates[maxm];

int output(int k) {
	for (int i = 1; i <= m; ++i) {
		int a = gates[i].a;
		int b = gates[i].b;
		int va = a < 0 ? -a > k : gates[a].out;
		int vb = b < 0 ? -b > k : gates[b].out;
		gates[i].out = !(va && vb);
	}
	return gates[m].out;
}

int solve(int vn) {
	int L = 0, R = n;
	while (L < R) {
		int x = L + (R - L) / 2;
		if (output(x) == vn) R = x;
		else L = x + 1;
	}
	return L;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; ++i)
			scanf("%d%d", &gates[i].a, &gates[i].b);
		int v0 = output(0);
		int vn = output(n);
		if (v0 == vn)
			for (int i = 1; i <= n; i++) printf("0");
		else {
			int ans = solve(vn);
			for (int i = 1; i < ans; ++i) printf("0");
			printf("x");
			for (int i = ans + 1; i <= n; i++) printf("1");
		}
		printf("\n");
	}
	return 0;
}