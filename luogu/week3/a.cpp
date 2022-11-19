#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 10;
int T;
char a[maxn];
int main() {
	scanf("%d", &T); getchar();
	for (int i = 1; i <= T; ++i) {
		int sum = 0, cnt = 0;
		while (~scanf("%c", &a[cnt]) && a[cnt] != 10) cnt++;
		for (int j = 0; j < cnt; ++j) sum += a[j] - '0';
		if (sum % 9 == 0) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}