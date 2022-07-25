#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;

const int maxn = 100000 + 5;
char p[maxn], z[3][maxn * 4];
char *s1 = z[0], *s2 = z[1], *s3 = z[2];
int kase, n, m, f[maxn];
LL ans[105];

void link_head(char *t, char *s) {
	int len = strlen(s);
	if (len <= m - 1) strcat(t, s);
	else strncat(t, s, m - 1);
}

void link_rear(char *t, char *s) {
	int len = strlen(s);
	if (len <= m - 1) strcat(t, s);
	else strcat(t, s + len - m + 1);
}

int KMP(char *s) {
	int j = 0, res = 0;
	for (int i = 0; s[i]; ++i) {
		while (j && s[i] != p[j]) j = f[j];
		if (s[i] == p[j]) j++;
		if (j == m) res++;
	}
	return res;
}

void init() {
	scanf("%s", p);
	m = strlen(p);
	strcpy(s1, "0"); strcpy(s2, "1");
	f[0] = f[1] = 0;
	for (int i = 1; p[i]; ++i) {
		int j = f[i];
		while (j && p[i] != p[j]) j = f[j];
		f[i + 1] = (p[i] == p[j] ? j + 1 : 0);
	}
	ans[0] = KMP(s1); ans[1] = KMP(s2);
}

int main() {
	while (~scanf("%d", &n)) {
		init();
		for (int i = 2; i <= n; ++i) {
			s3[0] = 0;
			link_rear(s3, s2); link_head(s3, s1);
			ans[i] = ans[i - 1] + ans[i - 2] + KMP(s3);
			s3[0] = 0;
			if (strlen(s2) >= m - 1 && strlen(s1) >= m - 1) {link_head(s3, s2); link_rear(s3, s1);}
			else {strcat(s3, s2); strcat(s3, s1);}
			char *temp = s1;
			s1 = s2; s2 = s3; s3 = temp;
		}
		printf("Case %d: %lld\n", ++kase, ans[n]);
	}
	return 0;
}