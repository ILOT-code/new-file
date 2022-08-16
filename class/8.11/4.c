#include<stdio.h>
#include<string.h>

int main() {
	char s1[50], s2[50];
	int len1, len2, dp[50][50], Max = 0, r = 0;
	int i, j;
	gets(s1 + 1); len1 = strlen(s1 + 1);
	gets(s2 + 1); len2 = strlen(s2 + 1);
	dp[0][0] = 0;
	for (i = 1; i <= len1; ++i)
		for (j = 1; j <= len2; ++j) {
			if (s1[i] == s2[j]) dp[i][j] = dp[i - 1][j - 1] + 1;
			else dp[i][j] = 0;
			if (dp[i][j] > Max) {
				Max = dp[i][j];
				r = i;
			}
		}
	if (Max == 0) printf("No Answer");
	else for (i = Max - 1; i >= 0; --i) printf("%c", s1[r - i]);
	return 0;

}