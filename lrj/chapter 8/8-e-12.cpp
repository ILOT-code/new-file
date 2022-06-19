#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int maxn = 800000 + 1000;
int n;

struct Node {
	int q, d;
	bool operator<(const Node &x) const {
		return d == x.d ? q < x.q : d < x.d;
	}
} A[maxn];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%d%d", &A[i].q, &A[i].d);
		sort(A, A + n);
		priority_queue<int> q;
		int ans = 0, t = 0;

		for (int i = 0; i < n; ++i) {
			if (t <= A[i].d - A[i].q) {
				t += A[i].q;
				ans++;
				q.push(A[i].q);
			}
			else if (!q.empty() && q.top() > A[i].q) {
				t += A[i].q - q.top();
				q.pop(); q.push(A[i].q);
			}
		}
		if (T) printf("%d\n\n", ans);
		else printf("%d\n", ans);
	}
	return 0;
}