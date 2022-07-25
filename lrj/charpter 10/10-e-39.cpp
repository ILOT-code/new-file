#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

const double PI = 2 * acos(0.0);
const int maxn = 500 + 5;
int n, r;
double A[maxn];

int main() {
	while (~scanf("%d%d", &n, &r) && n && r) {
		for (int i = 0; i < n; ++i) {
			scanf("%lf", &A[i]);
			A[i] = A[i] / 180 * PI;
		}
		sort(A, A + n);
		double sum = n * (n - 1) * (n - 2) / 6 * PI;
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j) {
				double  a = A[j] - A[i], s = (a - sin(a)) / 2;
				sum -= s * (n - 2 * j + 2 * i) + (j - i - 1) * PI;
			}
		if (n < 3) sum = 0;
		printf("%.0lf\n", round(sum * r * r));
	}
	return 0;
}