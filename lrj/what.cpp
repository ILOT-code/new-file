#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int main(){
	int a,b;
	for(int i = 0; i < 3; ++i){
		int c = scanf("%d%d",&a,&b);
		printf("%d\n",c);
		printf("%d\n",~c);
	}
	return 0;
}