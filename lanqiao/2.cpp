#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 5;
int L, R, pow_10[10];

int count(int x, int i) {
	int right = x % pow_10[i];
	int down = x - x % pow_10[i + 1];
	int up = down + pow_10[i + 1];
	int d = (x / pow_10[i]) % 10;
	if (d < 2) return down / 10;
	else if (d == 2) return down / 10 + right + 1;
	else return up / 10;

}
int cal(int x) {
	int t = x;
	int res = 0, len = 0;
	while (x > 0) len++, x /= 10;
	for (int i = 0; i < len; ++i)
		res += count(t, i);
	return res;
}
int main() {
	freopen("two.in", "r", stdin);
	freopen("two.out", "w", stdout);
	pow_10[0] = 1;
	for (int i = 1 ; i <= 9; ++i) pow_10[i] = 10 * pow_10[i - 1];
	printf("%d", cal(R) - cal(L - 1));
	fclose(stdin);
	fclose(stdout);

	return 0;
}