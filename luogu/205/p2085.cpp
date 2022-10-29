#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
#define fi first
#define se second
typedef pair<int, int> PII;


const int maxn = 10000 + 10;
int n, m;
int a[maxn], b[maxn], c[maxn], pos[maxn];
priority_queue <PII, vector<PII>, greater<PII>> q;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) scanf("%d%d%d", &a[i], &b[i], &c[i]);
	for (int i = 0; i < n; ++i) q.push(PII(a[i] + b[i] + c[i], i)), pos[i] = 1;
	int ans = 0;
	while (ans < m) {
		PII t = q.top(); q.pop();
		printf("%d ", t.fi);
		ans++, pos[t.se]++;
		q.push(PII(a[t.se]*pos[t.se]*pos[t.se] + b[t.se]*pos[t.se] + c[t.se], t.se));
	}
	return 0;
}
