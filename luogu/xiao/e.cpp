#include <cstdio>
#include <cmath>
#include<algorithm>
using namespace std;
int n;
int a[2*100005];
long long ANS=-100000000000;
long long fl(int i,int j)
{
    long long sum=i-j-1;
    for(int t=i;t<=j;++t)
        sum+=a[t];
    return sum;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;++i)
        for(int j=i;j<=n;++j)
    {
        long long t=fl(i,j);
        ANS=max(ANS,t);
    }
    printf("%lld",ANS);
}
