#include<cstdio>
using namespace std;

const int maxn = 100000 + 5;
int p[maxn], q[maxn], n;

int go(int start) {
	int ful = 0, x = start;
	do {
		ful += p[x] - q[x];
		x = (x + 1) % n;
		if (ful < 0 && x == start) return -1;
		if (ful < 0) return x;
	} while (x != start);
	return start;
};

int solve() {
	int start = 0;
	for (;;) {
		int end = go(start);
		if (end < start) return -1;
		if (end == start) return start;
		start = end;
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for (int kase = 1; kase <= T; kase++) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d", &p[i]);
		for (int i = 0; i < n; i++) scanf("%d", &q[i]);
		int ans = solve();
		printf("Case %d: ", kase);
		if (ans < 0) printf("Not possible\n");
		else printf("Possible from station %d\n", ans + 1);
	}
	return 0;
}