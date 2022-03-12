#include <cstdio>
#include <cstring>
#define maxn 10005
int main()
{
    int a[maxn],n,k;
    memset(a,0,sizeof(a));
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(j%i) continue;
            else
            {
                if(a[j]) a[j]=0;
                else     a[j]=1;
            }
        }

    }
    for(int i=1;i<=n;++i)
    if(a[i]) printf("%d ",i);
    return 0;
    
}