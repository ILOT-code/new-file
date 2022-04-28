//http://lx.lanqiao.cn/problem.page?gpid=T2300
//实在不知道这个勾八题的输入格式
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 20
using namespace std;
int dp[20][200],map[N][N];
int n,stac[20],top=0,ct=0;
int zhi(int i,int t)
{
    int ret=0;
    for(int ii=0;ii<n;++ii){
        if((t>>ii)&1) ret+=map[i][ii+1];
    }
    return ret;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;j++)
            scanf("%d",&map[i][j]);
    memset(dp,-1,sizeof(dp));
    for(int i=0;i<(1<<n);++i)
    if((i&(i<<1))==0)
    {
        stac[++top]=i;
        dp[1][top]=zhi(1,stac[top]);
    }
    for(int i=2;i<=n;++i){
        for(int j=1;j<=top;++j){
            for(int t=1;t<=top;++t){
                if(stac[j]&stac[t])      continue;
                if(stac[j]&(stac[t]<<1)) continue;
                if(stac[j]&(stac[t]>>1)) continue;
                if(dp[i-1][t]==-1)       continue;
                dp[i][j]=max(dp[i][j],dp[i-1][t]+zhi(i,stac[j]));
            }
        }
    }
    int ans=-1000;
    for(int i=1;i<=top;++i)
        ans=max(ans,dp[n][i]);
    printf("%d\n",ans);
    return 0;

}
