#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 2000 + 10;

char A[maxn], B[maxn];
int d[maxn][maxn];

int main() {
	scanf("%s%s", A + 1, B + 1);
	int len1 = 1, len2 = 1;
	while (A[len1] != 0) len1++;
	while (B[len2] != 0) len2++;

	for (int i = 1; i < len1; ++i) d[i][0] = i;
	for (int i = 1; i < len2; ++i) d[0][i] = i;
	for (int i = 1; i < len1; ++i)
		for (int j = 1;  j < len2; ++j)
			if (A[i] == B[j]) d[i][j] = d[i - 1][j - 1];
			else d[i][j] = min(d[i - 1][j - 1], min(d[i - 1][j], d[i][j - 1])) + 1;

	printf("%d\n", d[len1 - 1][len2 - 1]);
}