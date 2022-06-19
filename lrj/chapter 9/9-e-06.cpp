//这题输入格式纯纯脑瘫，Ud上也是错的，浪费时间。
#include<cstdio>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>
using namespace std;

const int maxn = 30 + 5;
int n, T, kase;
char s1[maxn], s2[maxn];
int d[maxn][maxn], num[maxn][maxn];

int main() {
	scanf("%d", &T);getchar();
	while (T--) {
		gets(s1),gets(s2);
		int len1 = strlen(s1), len2 = strlen(s2);
		for (int i = 0; i <= len1; ++i)
			for (int j = 0; j <= len2; ++j) {
				if (!i || !j) {
					d[i][j] = (i == 0 ? j : i);
					num[i][j] = 1;
				}
				else if (s1[i - 1] == s2[j - 1]) {
					d[i][j] = 1 + d[i - 1][j - 1];
					num[i][j] = num[i - 1][j - 1];
				}
				else {
					d[i][j] = min(d[i - 1][j], d[i][j - 1]) + 1;
					if (d[i - 1][j] == d[i][j - 1]) num[i][j] = num[i - 1][j] + num[i][j - 1];
					else if (d[i - 1][j] < d[i][j - 1]) num[i][j] = num[i - 1][j];
					else num[i][j] = num[i][j - 1];
				}
			}
		cout << "Case #" << ++kase << ": " << d[len1][len2] << " " << num[len1][len2] << "\n";
	}
	return 0;
}