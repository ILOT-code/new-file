//http://poj.org/problem?id=1185
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 105
#define M 11
int stack[60],map[N],n,m,top=0,dp[N][60][60],num[60];
bool bsf(int x)
{
    if(x&(x<<1)) return 0;
    if(x&(x<<2)) return 0;
    return 1;
}
bool fit(int x,int i)
{
    if(x&map[i]) return 0;
    return 1;
}
int count1(int x)
{
    int t=0;
    while(x)
    {
        t++;
        x&=(x-1);
    }
    return t;
}

int main()
{
    scanf("%d %d",&n,&m);
    getchar();
    for(int i=0;i<n;i++)  //画图
    {
        map[i]=0;
        for(int j=0;j<m;j++)
     {
        char s;
        scanf("%c",&s);
        if(s=='H') map[i]+=1<<j;
     }
     getchar();
    }
    for(int i=0;i<(1<<m);i++)
        if(bsf(i)) stack[top++]=i;//初始化stack数组，已排除与自身矛盾的情况。
    memset(dp,-1,sizeof(dp));
    for(int i=0;i<top;i++)
    {
        num[i]=count1(stack[i]);
        if(fit(stack[i],0)) dp[0][0][i]=num[i];
    }
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<top;j++)
          {
              if(!fit(stack[j],i))  continue;
              for(int t=0;t<top;t++)
                {
                    if(stack[j]&stack[t]) continue;
                    for(int k=0;k<top;k++)
                    {
                        if(stack[j]&stack[k]) continue;
                        if(dp[i-1][t][k]==-1)  continue;
                        dp[i][k][j]=max(dp[i][k][j],dp[i-1][t][k]+num[j]);
                    }
                }
          }
    }
    int ans=0;
    for(int j=0;j<top;j++)
    for(int k=0;k<top;k++)
    ans=max(ans,dp[n-1][j][k]);
    printf("%d\n",ans);
    return 0;
}
