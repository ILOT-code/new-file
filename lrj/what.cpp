//	freopen("C:\\Users\\lenovo\\Desktop\\test\\in.txt", "r", stdin);
//	freopen("C:\\Users\\lenovo\\Desktop\\test\\out.txt", "w", stdout);
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