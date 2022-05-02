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
	int d[10];
	memset(d,0x3f,sizeof d);
	for(int i = 0; i < 10; ++i)
		printf("%d\n",d[i]);
	return 0;
}
