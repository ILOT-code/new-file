#include<cstdio>
#include<cstring>
#include<string>
#include<stack>
#include<sstream>
#include<iostream>
#include<algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
typedef long long LL;
const int maxn = 600 + 5;

LL Gcd(LL a, LL b) {return b == 0 ? a : Gcd(b, a % b);}
struct Fraction {
	LL p, q;
	Fraction(LL a = 0, LL b = 1): p(a), q(b) { normal(p, q); }
	Fraction(const Fraction& x) {p = x.p; q = x.q;}
	void normal(LL& p, LL& q) { LL c = Gcd(p, q); p /= c; q /= c; }
	Fraction operator = (int a) {p = a; q = 1; return (*this);}
	Fraction operator = (LL a) {p = a; q = 1; return (*this);}
	Fraction operator - () { return Fraction(-p, q); }
	Fraction operator + (Fraction& x) {
		LL a, b;
		a = p * x.q + q * x.p;
		b = q * x.q;
		return Fraction(a, b);
	}
	Fraction operator += (Fraction& x) { return (*this) = (*this) + x; }
	Fraction operator - (Fraction& x) { return (-x) + (*this); }
	Fraction operator -= (Fraction& x) { return (*this) = (*this) - x; }
	Fraction operator * (Fraction& x) {
		LL a, b;
		a = p * x.p;
		b = q * x.q;
		return Fraction(a, b);
	}
	Fraction operator *= (Fraction& x) { return (*this) = (*this) * x; }
	Fraction operator / (Fraction& x) { return Fraction(x.q, x.p) * (*this); }
	Fraction operator /= (Fraction& x) { return (*this) = (*this) / x; }
	bool operator == (const Fraction& x) { return p * x.q == q * x.p; }
	bool operator == (const int x) { return p == x * q; }
	bool operator < (Fraction& x) { return p * x.q < q * x.p; }
	void print() { normal(p, q); if (q < 0) q = -q, p = -p; printf("%lld/%lld\n", p, q); }
};

struct Node {
	Node *l, *r;
	Fraction f;
	int op;
	bool is_x;
	Node() {};
	Node(Fraction& c, Node* a = NULL, Node* b = NULL): f(c), l(a), r(b) {};
} nodes[maxn];

Fraction calc(Fraction& a, Fraction& b, int op) {
	switch (op) {
	case 0: return a + b; break;
	case 1: return a - b; break;
	case 2: return a * b; break;
	case 3: return a / b; break;
	default: return Fraction(0, 0);
	}
}

int op_int(char ch) {
	if (ch == '+') return 0;
	if (ch == '-') return 1;
	if (ch == '*') return 2;
	if (ch == '/') return 3;
	return -1;
}
int revop(int op) { return op ^ 1; }

string s;
Fraction ans;

Node* build_tree() {
	stringstream ss;
	ss << s;
	int cnt = 0;
	stack<Node*> stac;
	while (ss >> s) {
		Node& cur = nodes[cnt];
		int opint = op_int(s[0]);
		if (opint >= 0) {
			cur.op = opint;
			cur.r = stac.top(); stac.pop();
			cur.l = stac.top(); stac.pop();
			cur.is_x = cur.l->is_x || cur.r->is_x;
			if (cur.is_x) {
				if ((cur.op == 2 && (cur.l->is_x ? cur.r->f == 0 : cur.l->f == 0)) || (cur.op == 3 && cur.r->is_x && cur.l->f == 0)) {
					cur.is_x = false;
					cur.f = 0; cur.l = cur.r = NULL;
				}
			}
			else {
				cur.f = calc(cur.l->f, cur.r->f, opint);
				cur.l = cur.r = NULL;
			}
		}
		else {
			cur.l = cur.r = NULL;
			if (s[0] == 'X') cur.is_x = true;
			else {
				cur.is_x = false;
				int num = s[0] - '0';
				cur.f = num;
			}
		}
		stac.push(nodes + cnt++);
	}
	return stac.top();
}

bool dfs(Node* root) {
	if (root->l == NULL) return true;
	if (root->l->is_x) {
		ans = calc(ans, root->r->f, revop(root->op));
		if (!dfs(root->l)) return false;
	}
	else {
		if (root->op % 2 == 0) ans = calc(ans, root->l->f, revop(root->op));
		else ans = calc(root->l->f, ans, root->op);
		if (ans.q == 0) return false;
		if (!dfs(root->r)) return false;
	}
	return true;
}

int main() {
	while (getline(cin, s)) {
		Node* root = build_tree();
		if (!root->is_x) {
			if (root->f == 0) printf("MULTIPLE\n");
			else printf("NONE\n");
			continue;
		}
		ans = 0;
		if (dfs(root)) { printf("X = "); ans.print(); }
		else { printf("NONE\n"); }
	}
	return 0;
}
