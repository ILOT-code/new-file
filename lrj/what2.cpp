#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<cstdlib>
using namespace std;


int main() {
	int T;
	scanf("%d", &T);
	printf("%d\n", T);
	srand(time(0));
	while (T--) {
		int n = rand() % 21;
		printf("%d\n", n + 1);
		for (int i = 1; i <= n + 1; ++i) {
			int k = rand() % n;
			for (int j = 0; j < k + 1; ++j) {
				int out = rand() % n;
				if (out + 1 != i)
					printf("%d ", out + 1);
			}
			printf("\n");
		}
	}
	return 0;

}