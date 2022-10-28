#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

int n, ans;
priority_queue<int, vector<int>, greater<int>> q;

int main() {
	scanf("%d", &n);
	for (int i = 1, x; i <= n; ++i) scanf("%d", &x), q.push(x);

	while (q.size() > 1) {
		int a = q.top(); q.pop();
		int b = q.top(); q.pop();
		ans += a + b;
		q.push(a + b);
	}
	printf("%d\n", ans);
}