//http://poj.org/problem?id=1186
//不用map,改用快速排序+二分统计。
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
int n,T,k[7],p[7],ans=0,num[3375000+5],ct=0;
int quick_pow(int w,int b)
{
    int s=1;
    while (b) {if (b&1) s*=w;b>>=1;if (b) w*=w;}
    return s;
}
void bfs(int m,ll now)
{
    if(m==n/2)
    {
        num[ct++]=now;
        return;
    }
    for(int i=1;i<=T;++i)
        bfs(m+1,now+k[m]*quick_pow(i,p[m]));
}
int Find(int x)
{
    int L=0,R=ct-1,l;
    while(L<=R)
    {
        int mid=L+(R-L)/2;
        if(x<=num[mid]) R=mid-1;
        else L=mid+1;
    }
    l=L;L=0;R=ct-1;
    while(L<=R)
    {
        int mid=L+(R-L)/2;
        if(x>=num[mid]) L=mid+1;
        else R=mid-1;
    }
    return R-l+1;
}
void bfs1(int m,ll now)
{
    if(m==n-n/2)
    {
        ans+=Find(-now);
        return;
    }
    for(int i=1;i<=T;++i)
        bfs1(m+1,now+k[m+n/2]*quick_pow(i,p[m+n/2]));
}
int main()
{
    scanf("%d%d",&n,&T);
    for(int i=0;i<n;++i)
        scanf("%d%d",k+i,p+i);
    bfs(0,0);
    sort(num,num+ct);
    bfs1(0,0);
    printf("%d\n",ans);
    return 0;
}
