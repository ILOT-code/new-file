//https://loj.ac/p/10022
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=105;
int a,b,v[maxn],ans[maxn],maxd;
int gcd(int a,int b) {return b==0?a:gcd(b,a%b);}
int get_first(int a,int b)  {return b/a+1;}
bool better(int d)
{
    for(int i=d;i>=0;--i)
        if(v[i]!=ans[i])  return ans[i]==-1||v[i]<ans[i];
    return false;
}
bool dfs(int d,int from,int a,int b)
{
    if(d==maxd)
    {
        if(b%a) return false;
        v[d]=b/a;
        if(better(d)) memcpy(ans,v,sizeof(int)*(d+1));
        return true;
    }
    bool ok=false;
    from=max(from,get_first(a,b));
    for(int i=from;;++i)
    {
        if(b*(maxd+1-d)<=i*a) break;
        v[d]=i;
        int b2=b*i;
        int a2=a*i-b;
        int g=gcd(a2,b2);
        if(dfs(d+1,i+1,a2/g,b2/g)) ok=true;
    }
    return ok;
}
int main()
{
    while(scanf("%d%d",&a,&b)==2)
    {
        int ok=0;
        for(;maxd<=100;++maxd)
        {
            memset(ans,-1,sizeof(ans));
            if(dfs(0,get_first(a,b),a,b))
            {
                ok=1;
                break;
            }
        }
        if(ok)
        for(int i=0;i<=maxd;++i) printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}
