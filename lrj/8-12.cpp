#include <cstdio>
using namespace std;

inline int pow(int k, int t) {  //return t^k;
	if (k == 0) return 1;
	return t * pow(k - 1, t);
}

int F(int k, int i) {
	if (i < 0) return 0;
	if (k == 0 ) return 1;
	if (i >= pow(k - 1, 2)) return F(k - 1, i - pow(k - 1, 2)) + pow(k - 1, 3) * 2;
	else return 2 * F(k - 1, i);
}

int main () {
	int k, A, B;
	scanf("%d%d%d", &k, &A, &B);
	printf("%d", F(k, B) - F(k, A - 1));
	return 0;
}