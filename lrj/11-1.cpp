#include<cstdio>
#include<map>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 60000;
int T, kase, cnt;
char expr[maxn * 5], *p;
int done[maxn];

struct Node {
	string s;
	int hash, left, right;
	bool operator<(const Node& rhs) const {
		if (hash != rhs.hash) return hash < rhs.hash;
		if (left != rhs.left) return left < rhs.left;
		return right < rhs.right;
	}
} node[maxn];
map<Node, int> dict;

int parse() {
	int id = cnt++;
	Node& u = node[id];
	u.left = u.right = -1;
	u.s = "";
	u.hash = 0;

	while (isalpha(*p)) {
		u.hash = u.hash * 26 + *p - 'a' + 1;
		u.s.push_back(*p);
		p++;
	}

	if (*p == '(') {
		p++; u.left = parse(); p++; u.right = parse(); p++;
	}
	if (dict.count(u) != 0) {
		cnt--;
		return dict[u];
	}
	return dict[u] = id;
}

void print(int v) {
	if (done[v] == kase) printf("%d", v + 1);
	else {
		done[v] = kase;
		printf("%s", node[v].s.c_str());
		if (node[v].left != -1) {
			putchar('(');
			print(node[v].left);
			putchar(',');
			print(node[v].right);
			putchar(')');
		}
	}
}

int main() {
	scanf("%d", &T);
	while (T--) {
		kase++;
		dict.clear(); cnt = 0;
		scanf("%s", expr); p = expr;
		print(parse());
		puts("");
	}
	return 0;
}