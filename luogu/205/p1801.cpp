#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

priority_queue<int> dn;
priority_queue<int, vector<int>, greater<int>> up;
const int maxn = 200000 + 10;
int n, m, a[maxn], u[maxn];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	int l = 1, r;
	for (int i = 1; i <= m; ++i) {
		scanf("%d", &r);
		while (l <= r) {
			dn.push(a[l++]);
			if (dn.size() == i) { up.push(dn.top()); dn.pop(); }
		}
		printf("%d\n", up.top());
		dn.push(up.top()); up.pop();
	}
	return 0;
}