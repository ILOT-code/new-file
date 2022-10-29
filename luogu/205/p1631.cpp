#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
#define fi first
#define se second
typedef pair<int, int> PII;

const int maxn = 100000 + 10;
int n, a[maxn], b[maxn], pos[maxn];
priority_queue<PII, vector<PII>, greater<PII>> q;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
	for (int i = 1; i <= n; ++i) q.push(PII(a[i] + b[1], i)), pos[i] = 1;
	int ans = 0;
	while (ans < n) {
		PII t = q.top(); q.pop();
		printf("%d ", t.fi); pos[t.se]++;
		q.push(PII(a[t.se] + b[pos[t.se]], t.se));
		ans++;
	}
	return 0;
}