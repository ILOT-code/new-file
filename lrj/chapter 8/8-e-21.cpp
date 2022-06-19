#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		int t = c / 3, end = 0;
		if (c % 3 == 0) {
			for (int i = 0; i <= t; ++i) printf("%d ", 3 * i);
			for (int i = 0; i <= t; ++i) printf("%d ", 3 * t + 1 - 3 * i);
			for (int i = 0; i <= t; ++i) printf("%d ", 2 + 3 * i);
			end = 3 * t + 2;
			a -= 2;
		} else if (c % 3 == 1) {
			for (int i = 0; i <= t + 1; ++i) printf("%d ", 3 * i);
			for (int i = 0; i <= t; ++i) printf("%d ", 3 * t + 1 - 3 * i);
			for (int i = 0; i <= t; ++i) printf("%d ", 2 + 3 * i);
			printf("%d ", 3 * t + 1 + 3);
			end = 3 * t + 4;
			a -= 1;
			b -= 2;
		} else if (c % 3 == 2) {
			for (int i = 0; i <= t + 1; ++i) printf("%d ", 3 * i);
			for (int i = 0; i <= t; ++i) printf("%d ", 3 * t + 1 - 3 * i);
			for (int i = 0; i <= t + 1; ++i) printf("%d ", 2 + 3 * i);
			printf("%d %d ", 3 * t + 2 + 2, 3 * t + 2 + 4);
			end = 3 * t + 6;
			a -= 2;
			b -= 2;
		}
		
		while (a-- > 1) printf("%d ", ++end);
		t = b / 2 + (b % 2);
		for (int i = 0; i < t; ++i) printf("%d ", end += 2);
		printf("%d ", end += ((b % 2) ? -1 : 1));
		b -= t;
		while (b--) {
			if (b) printf("%d ", end -= 2);
			else printf("%d", end -= 2);
		}
		printf("\n");
	}
	return 0;
}