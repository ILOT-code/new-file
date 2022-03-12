//http://poj.org/problem?id=1186
//用map来坐标记会超时
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define ll long long
using namespace std;
int n,T,k[7],p[7],ans=0;
map<ll,int>f;
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
        ++f[now];
        return;
    }
    for(int i=1;i<=T;++i)
        bfs(m+1,now+k[m]*quick_pow(i,p[m]));
}
void bfs1(int m,ll now)
{
    if(m==n-n/2)
    {
        if(f.count(-now)) ans+=f[-now];
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
    bfs1(0,0);
    printf("%d\n",ans);
    return 0;
}
