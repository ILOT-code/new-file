#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;

int LL_len(LL x){
    int len = 1;
    while(x = x/10) len++;
    return len;
}
int main() {
	int x;
	while (scanf("%d", &x)) printf("%d\n", LL_len(x));
	return 0;
}