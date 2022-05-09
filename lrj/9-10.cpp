//s最终必须变成一个正规的括号序列，由定义知，它必然是[s']或(s')或AB型的。
//不管match(i,j)是否为真，它都能被拓展为AB型。
//若match(i,j)为真，那么它可以不经过额外消耗转化为[s']或(s'),因此需要考虑。
//而若match(i,j)为假，例如为(....];
//也可以拓展为[s']型，多加一个括号就可以，如(....]),但这一定不会比AB型更优。
//因为容易看出，上面这种构造的最低消耗是和d[i][i]+d[i+1][j]一样的。
//因此就得到了下面的状态转移函数。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;
char s[maxn];
int n, d[maxn][maxn];

bool match(int i, int j) {
	return (s[i] == '(' && s[j] == ')') || (s[i] == '[' && s[j] == ']');
}
void dp() {
	for (int i = 0; i < n; ++i) d[i][i]  = 1;
	for (int len = 2; len <= n; ++len)
		for (int i = 0; i + len - 1 < n; ++i) {
			int j = i + len - 1;
			d[i][j] = maxn;
			if (match(i, j)) d[i][j] = (j == i + 1 ? 0 : d[i + 1][j - 1]);
			for (int k = i; k < j; ++k)
				d[i][j] = min(d[i][j], d[i][k] + d[k + 1][j]);
		}
}

void print(int i, int j) {
	if (i > j) return;
	if (i == j) {
		if (s[i] == '(' || s[i] == ')') printf("()");
		else printf("[]");
		return;
	}
	int ans = d[i][j];
	if (match(i, j) && (d[i + 1][j - 1] == ans || j == i + 1)) {
		printf("%c", s[i]); print(i + 1, j - 1); printf("%c", s[j]);
		return;
	}
	for (int k = i; k < j; k++)
		if (ans == d[i][k] + d[k + 1][j]) {
			print(i, k); print(k + 1, j);
			return;
		}
}

int main() {
	int T;	
	scanf("%d", &T); getchar();
	while (T--) {
		gets(s); gets(s);
		n = strlen(s);
		dp();
		print(0, n - 1);
		printf("\n");
		if (T) printf("\n");
	}
	return 0;
}