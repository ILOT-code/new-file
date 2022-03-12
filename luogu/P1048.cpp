//https://www.luogu.com.cn/problem/P1048
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int T,M,f[1005],t,v;
int main()
{
    scanf("%d %d",&T,&M);
    memset(f,-1,sizeof(f));
    f[0]=0;
    int ans=0;
    for(int i=1;i<=M;++i){
        scanf("%d %d",&t,&v);
        for(int j=T-t;j>=0;--j)
            if(f[j]!=-1)
                if(f[j+t]<f[j]+v)
            {
                f[j+t]=f[j]+v;
                ans=max(ans,f[j+t]);
            }
    }
     printf("%d\n",ans);
     return 0;
}
