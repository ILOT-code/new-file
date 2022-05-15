#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn = 5000 + 10;
int a[maxn], n, m, cnt;
vector<int> b;

bool cmp(int a, int b) {
	return abs(a - cnt) < abs(b - cnt);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
	for (int i = 0; i < m; ++i) {
		int x;
		scanf("%d", &x);
		b.push_back(x);
	}
	sort(a, a + n);
	sort(b, b + m);
	printf("%d", ans);
	return 0;
}