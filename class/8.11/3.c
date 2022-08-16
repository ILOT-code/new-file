#include<stdio.h>

struct DATE {
	int y, m, d;
};
int Big_mon(int m) {
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) return 1;
	return 0;
}
int Run_yea(int y) {
	if ((y % 4 == 0 && y % 100) || (y % 400 == 0)) return 1;
	return 0;
}
int main() {
	struct DATE T;
	scanf("%d %d %d", &T.y, &T.m, &T.d);
	int ans = 0, i;
	for (i = 1; i < T.m; ++i) {
		if (Big_mon(i)) ans += 31;
		else if (i == 2) ans += 28 + Run_yea(T.y);
		else ans += 30;
	}
	printf("%d", ans + T.d);
	return 0;
}