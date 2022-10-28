#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

int n;
priority_queue<int, vector<int>, less<int>> dn;
priority_queue<int, vector<int>, greater<int>> up;

int main() {
	scanf("%d", &n);
	for (int i = 1, t; i <= n; ++i) {
		scanf("%d", &t);
		dn.push(t);
		up.push(dn.top()); dn.pop();
		if (i & 1) {dn.push(up.top()); up.pop(); printf("%d\n", dn.top());}
	}
	return 0;
}