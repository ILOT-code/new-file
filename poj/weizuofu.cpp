//http://poj.org/problem?id=1067
#include <cstdio>
#include <cmath>
int main()
{
    long a,b,c;
    while(scanf("%ld %ld",&a,&b)!=EOF)
    {
    if(a>b) {c=a;a=b;b=c;}
    long t=abs(a-b);
    long p=t*(1.0+sqrt(5.0))/2.0;
    if(p==a) printf("0\n");
    else printf("1\n");
    }
    return 0;
}
