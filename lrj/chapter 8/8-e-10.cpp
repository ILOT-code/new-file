#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
int a[maxn], n, id[maxn];

bool com(int x, int y) {
	return a[x] > a[y];
}
int main() {
	while (~scanf("%d", &n)) {
		long long sum = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			sum += a[i];
			id[i] = i;
		}
		if (sum & 1) {printf("No\n"); continue;}
		
		sort(id, id + n, com);
		sum >>= 1;
		for (int i = 0; i < n; ++i) {
			int t = id[i];
			if (a[t] <= sum) {
				sum -= a[t];
				a[t] = 1;
			}
			else a[t] = -1;
		}
		printf("Yes\n");
		for (int i = 0; i < n; ++i) printf("%d ", a[i]);
		printf("\n");
	}
	return 0;
}