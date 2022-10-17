#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 500000 + 10;
int cnt, mmax[maxn][2], mmin[maxn][2];
char a[maxn];

void dfs(int root) {
	if (a[root] == '0') {
		mmax[root][1] = mmin[root][1] = 1;
		mmax[root][0] = mmin[root][0] = 0;
		return;
	}
	if (a[root] == '1') {
		dfs(++cnt);
		mmax[root][1] = mmax[root + 1][0] + 1;
		mmax[root][0] = max(mmax[root + 1][0], mmax[root + 1][1]);
		mmin[root][1] = mmin[root + 1][0] + 1;
		mmin[root][0] = min(mmin[root + 1][0], mmin[root + 1][1]);
		return;
	}
	if (a[root] == '2') {
		dfs(++cnt);
		int k = cnt + 1; dfs(++cnt);
		mmax[root][1] = mmax[root + 1][0] + mmax[k][0] + 1;
		mmax[root][0] = max(mmax[root + 1][0] + mmax[k][1], mmax[root + 1][1] + mmax[k][0]);
		mmin[root][1] = mmin[root + 1][0] + mmin[k][0] + 1;
		mmin[root][0] = min(mmin[root + 1][0] + mmin[k][1], mmin[root + 1][1] + mmin[k][0]);
		return;
	}
}

int main() {
	scanf("%s", a);
	dfs(cnt);
	printf("%d %d\n", max(mmax[0][1], mmax[0][0]), min(mmin[0][1], mmin[0][0]));
	return 0;
}