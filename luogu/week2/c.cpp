#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n;
bool a[15], vis[1 << 12];

int cal1(int s) {
	int ret = 0;
	for (int i = 0; i < n; ++i) {
		if ((s & (1 << i)) != a[n - i]) ret++;
	}
	return ret;
}
int trans(int p) {
	int ret = 0;
	for (int i = p; i <= n; ++i)
		if (a[i] == 1) ret |= (1 << (n - p));
	return ret;

}
int cal2(int s) {
	int ret = 0;
	for (int len = n; len > 0; --len) {
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n + 1 - len; ++i) {
			int state = trans(i);
			if (vis[state]) continue;
			else {
				ret++;
				vis[state] = 1;
			}
		}
	}
	return ret;
}
void print(int s) {
	for (int i = n - 1; i >= 0; --i)
		printf("%d", s & (1 << i));
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%1d", &a[i]);
	int max_x = 0, max_z = 0, max_s = 0;
	for (int s = 0; s < (1 << n); ++s) {
		int op = cal1(s);
		int t = cal2(s);
		if (t > max_x) {
			max_x = t;
			max_z = op;
			max_s = s;
		}
		if (t == max_x) {
			if (op < max_z) {
				max_z = op;
				max_s = s;
			}
		}

	}
	print(max_s);
	return 0;
}