#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxn = 2 * 100000 + 10;
const int maxq = 5 * 100000 + 10;
int a[maxn], n, q, ID[maxn], func1 = -1;

void caozuo(int k) {
	int f, x, y;
	scanf("%d", &f);
	if (f == 1) {
		scanf("%d", &x);
		if(func1 == -1 || x < func1) func1 = x;
		if(k == q-1)
			for(int i = 0; i < n; ++i)
				if(a[i] > func1) a[i] = func1;
	} else if (f == 2) {
		if(func1 != -1){
			for(int i = 0; i < n; ++i)
				if(a[i] > func1) a[i] = func1;
			func1 = -1;
		}
		scanf("%d%d", &x, &y);
		a[x-1] = y;
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
	scanf("%d", &q);
	for (int i = 0; i < q; ++i) caozuo(i);
	for (int i = 0; i < n; ++i) printf("%d ", a[i]);
	return 0;


}