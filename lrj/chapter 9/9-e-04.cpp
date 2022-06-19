//令大写字母A,B,等代表一个合法折叠式。
//对于一个子序列str(i,j),它最简后只有两种可能，x(A)型与AB型。
//如果它是AB形，那么它必然被分开了，那就从i到j-1枚举k,即可找到AB型的最小长度。
//再判断它是否为x(A)型，如果是，则枚举找到它的最小的一个重复序列,设长度为len.
//对于这个最小序列，它本身不可能被简化为x(A)型，否则矛盾，则它只能是AB型。
//则把它简化为最小的A'B'型，那么原序列就可以被简化为x(A'B')，x=(j-1+1)/len.
//对于其它不是最小的重复子序列，只有一种可能，就是它是最小重复子序列的重复，所以不考虑。
//证明：若最小重复子序列长度为L，另一重复子序列长度为kL.设k为一个小数，其小数是部分k',有：
//str[x]=str[x+L],str[x]=str[x+kL]
//整理后得到str[x]=xtr[x+k'L],则得到了另一最小重复子序列，长度为k'L,矛盾。
#include<cstring>
#include<sstream>
#include<iostream>
using namespace std;

const int maxn = 100 + 5;
const int INF = 1 << 20;
int d[maxn][maxn];
string str, sub[maxn][maxn];

int fold(int l, int r) {
	for (int len = 1; len <= (r - l + 1) / 2; ++len) {
		int flag = 1;
		if ((r - l + 1) % len) continue;
		for (int j = l; j + len <= r; ++j) {
			if (str[j] != str[j + len]) {
				flag = 0;
				break;
			}
		}
		if (flag) return len;
	}
	return 0;
}
int dp(int l, int r) {
	int &ans = d[l][r];
	if (ans != -1) return ans;
	if (l == r) {sub[l][r] = str[l]; return ans = 1;}
	ans = INF;
	int pos = l;
	for (int i = l; i < r; ++i)if (dp(l, i) + dp(i + 1, r) < ans) {
			ans = dp(l, i) + dp(i + 1, r);
			pos = i;
		}
	sub[l][r] = sub[l][pos] + sub[pos + 1][r];
	int len = fold(l, r);
	if (len) {
		char tmp[5];
		sprintf(tmp, "%d", (r - l + 1) / len);
		string newstr = (string)tmp + "(" + sub[l][l + len - 1] + ")";
		if (newstr.size() < ans) {
			ans = newstr.size();
			sub[l][r] = newstr;
		}
	}
	return ans;
}
int main() {
	while (cin >> str) {
		memset(d, -1, sizeof(d));
		int right = str.length() - 1;
		dp(0, right);
		cout << sub[0][right] << endl;
	}
	return 0;
}