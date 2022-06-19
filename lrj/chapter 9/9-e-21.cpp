//这种操作是对称的，对A的修改等于对B的修改，对A的插入等于对B的删除，对A的删除等于对B的插入。
//因此，可以仅仅对其中一个串操作，另一个不操作。设对x操作，对y不操作。
//对一个字母的修改只有一次，不可能对一个字母修改两次，且对一个字母修改后不可能再删除它。
//在上面的基础上，可以得到，操作的顺序是可以改变的。
//dp[i][j]表示操作x的1~i号字母来变成y的1~j。
//设当前考虑到dp[i][j],y是不变的，总有一个数要对应y[j],有三种可能：
//x[i]还存在，并且对应了y[j],则是直接修改x[i].把这个操作最先进行，为dp[i-1][j-1]+(x[i]==x[j])?0:1;
//x[i]还存在，但不对应y[j],则必然在x[i]后面插入了一个和y[j]相同的数，把这个操作先进行，为dp[i][j-1]+1;
//x[i]不存在，则x[i]被删除了，把这个操作先进行，为dp[i-1][j]+1;
//对于x的分段问题，下面的代码给了很好的解答。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 5000 + 5;
const int maxm = 50 + 5;
char x[maxn], y[maxm];
int n, m, dp[maxn][maxm];

bool judge(int mid) {
	for (int i = 0; i <= n; ++i) dp[i][0] = i;
	for (int i = 0; i <= m; ++i) dp[0][i] = i;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			dp[i][j] = dp[i - 1][j - 1] + (x[i] == y[j] ? 0 : 1);
			dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
			dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
		}
		if (dp[i][m] <= mid) dp[i][0] = 0;//分段
	}
	return dp[n][m] <= mid;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%s%s", y + 1, x + 1);
		n = strlen(x + 1), m = strlen(y + 1);
		int l = 0, r = m;
		while (l < r) {
			int mid = l + (r - l) / 2;
			if (judge(mid)) r = mid;
			else l = mid + 1;
		}
		printf("%d\n", l);
	}
	return 0;
}