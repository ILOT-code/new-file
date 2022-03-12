#include <cmath>
#include<cstdio>
using namespace std;
#define inf 0.000000001
int main()
{
    int a;
    while(scanf("%d",&a)!=EOF){
    int t=floor(-2*(a+sqrt(1+a*a)));
    double k=(-t+sqrt(t*t-4+4*a*t))/2.0;
    while(abs(k-floor(k))>inf)
    {
        t=t-1;
        k=(-t+sqrt(t*t-4+4*a*t))/2.0;
    }
    printf("%d\n",-t);}
    return 0;
}
//poj上无法编译通过。
