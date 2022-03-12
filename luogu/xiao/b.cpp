#include <cstdio>
using namespace std;
long long T;
int main()
{
    scanf("%lld",&T);
    for(long long i=1;i<=T;++i)
    {
        long long m,n,x1,x2,y1,y2;
        scanf("%lld %lld",&m,&n);
        scanf("%lld %lld %lld %lld",&x1,&y1,&x2,&y2);
        long long t=x1-x2+y1-y2;
        if(t%2==0) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}
