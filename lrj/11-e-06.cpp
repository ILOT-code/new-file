#include<cstdio>
#include<ctype.h>
#include<map>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 2000;

int lch[maxn], rch[maxn], op[maxn], nc;
char str[maxn];
map<char, char> inv_op;

int build_tree(int L, int R) {
	if (R - L == 1) {
		int id = ++nc;
		op[id] = str[L];
		lch[id] = rch[id] = 0;
		return id;
	}
	int c1 = -1, c2 = -1, p = 0;
	for (int i = L; i < R; ++i) {
		switch (str[i]) {
		case '(': p++; break;
		case ')': p--; break;
		case '+': case '-': if (!p) c1 = i; break;
		case '*': case '/': if (!p) c2 = i; break;
		}
	}
	if (c1 < 0) c1 = c2;
	if (c1 < 0) return build_tree(L + 1, R - 1);
	int id = ++nc;
	op[id] = str[c1];
	lch[id] = build_tree(L, c1);
	rch[id] = build_tree(c1 + 1, R);
	return id;
}

void dfs(int u, int INV, int inv) {
	if (isalpha(op[u])) {putchar(op[u]); return;}
	switch (op[u]) {
	case '+': case '-':
		dfs(lch[u], 0, inv);
		putchar(inv == 1 ? inv_op[op[u]] : op[u]);
		dfs(rch[u], 0, op[u] == '+' ? inv : !inv);
		break;
	case '*': case '/':
		if (op[lch[u]] == '+' || op[lch[u]] == '-') {
			putchar('('); dfs(lch[u], 0, 0); putchar(')');
		}
		else dfs(lch[u], INV, 0);
		putchar(INV == 1 ? inv_op[op[u]] : op[u]);
		if (op[rch[u]] == '+' || op[rch[u]] == '-') {
			putchar('('); dfs(rch[u], 0, 0); putchar(')');
		}
		else dfs(rch[u], op[u] == '*' ? INV : !INV, 0);
		break;
	}

}

int main() {
	inv_op['+'] = '-', inv_op['-'] = '+';
	inv_op['*'] = '/', inv_op['/'] = '*';
	while (~scanf("%s", str)) {
		nc = 0;
		build_tree(0, strlen(str));
		dfs(1, 0, 0); putchar('\n');
	}
	return 0;
}
