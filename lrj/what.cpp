#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
int gcd(int a,int b){
    return !b? a : gcd(b,a%b);
}
int main(){
	for(int i = 0; i < 5; ++i){
		int a, b;
		scanf("%d%d", &a,&b);
		int t = gcd(a,b);
		printf("%d\n", t);
	}


	return 0;
}