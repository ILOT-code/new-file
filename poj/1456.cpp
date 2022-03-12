//http://poj.org/problem?id=1456
#include<cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
struct work
{
    int p,d;
    bool operator< (work a)
    {
        if(p==a.p) return d>a.d;
        return p>a.p;
    }
}w[10005];
bool t[10005];
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        int i,j;
        memset(t,0,sizeof(t));
        for(int i=1;i<=n;++i)
            scanf("%d%d",&w[i].p,&w[i].d);
        sort(w+1,w+n+1);
        int ans=0;
        for(int i=1;i<=n;++i)
            for(j=w[i].d;j>=1;--j)
            if(!t[j])
        {
            ans+=w[i].p;
            t[j]=1;
            break;
        }
        printf("%d\n",ans);
    }
    return 0;
}
