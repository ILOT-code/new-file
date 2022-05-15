#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int main() {
	int a, b, c;
	long long int ans = 1;
	scanf("%d%d%d", &a, &b, &c);
	for(int i = 0; i < b; ++i){
		ans = (ans*a)%c;
	}
	printf("%lld",ans);

}