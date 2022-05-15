#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<cstdlib>
using namespace std;
int ksm(int a, int k){
	int rec = 1;
	while(k){
		if(k&1) rec *= a%
		a*=a;
		k >>= 1;
	}
	return rec;
}

int main() {
	int T;
	int a = 3, b = 5;
	printf("%d", ksm(a,b));

	return 0;

}