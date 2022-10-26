#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 150000 + 10;
int n, ans;
LL T = 0;
priority_queue<int> Q;
struct Node {
	int spend, dead;
	Node(int s = 0, int d = 0): spend(s), dead(d) {}
	bool operator<(const Node& rhs) { return dead < rhs.dead;}
} nodes[maxn];

int main() {
	scanf("%d", &n);
	for (int i = 0, s, d; i < n; ++i) {
		scanf("%d%d", &s, &d);
		nodes[i] = Node(s, d);
	}
	sort(nodes, nodes + n);

	for (int i = 0; i < n; ++i) {
		if (T + nodes[i].spend <= nodes[i].dead) {
			T += 1LL * nodes[i].spend;
			Q.push(nodes[i].spend);
			ans++;
			continue;
		}
		if (nodes[i].spend < Q.top()) {
			T += 1LL * (nodes[i].spend - Q.top());
			Q.pop(); Q.push(nodes[i].spend);
		}
	}
	printf("%d\n", ans);
	return 0;
}