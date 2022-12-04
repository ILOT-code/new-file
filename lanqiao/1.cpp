#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 5;
int n, a[maxn];
struct Person {
	int t, id;
	bool operator<(Person rhs) {return t < rhs.t;};
} p[maxn];
int main() {
	scanf("%d", &n);
	int ans = 0;
	for (int i = 1; i <= n; ++i) scanf("%d", &p[i].t), p[i].id = i;
	sort(p + 1, p + 1 + n);
	for (int i = 2; i <= n; ++i) a[i] = a[i - 1] + p[i - 1].t, ans += a[i];
	printf("%.2lf", (double)ans / n);
	return 0;
}