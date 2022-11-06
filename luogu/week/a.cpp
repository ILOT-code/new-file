#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 200000 + 10;
int n;
char s[maxn], t[maxn];

int main() {
	scanf("%d", &n);
	scanf("%s", s);
	scanf("%s", t);
	int ans = 0;
	for (int i = 0; i < n; ++i)if (s[i] == t[i])ans++;
	printf("%d\n", ans);
	return 0;
}