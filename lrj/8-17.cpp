#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
int next[12];

int main(){
	int a, b;
	scanf("%d%d",&a,&b);
	
	next[1] = a+b+100;
	printf("%d",next[1]);
	return 0;
}