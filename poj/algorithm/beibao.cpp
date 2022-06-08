#include <bits/stdc++.h>
using namespace std;
#define N 2005
int main()
{
    int w,n,P;
    int weight[N],value[N],p[N];
    scanf("%d%d%d",&n,&w,&P);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&weight[i],&value[i],&p[i]);
    int tu[N][N][11];
    memset(tu,0,sizeof(tu));
    for(int i=1;i<=n;i++)
{
    for(int j=0;j<=w;j++)
        for(int t=0;t<=P;t++)
            tu[i][j][t]=tu[i-1][j][t];
    for(int j=weight[i];j<=w;j++)
        for(int t=p[i];t<=P;t++)
        tu[i][j][t]=max(tu[i][j][t],value[i]+tu[i-1][j-weight[i]][t-p[i]]);
}
    int  ans=0;
    for(int j=0;j<=w;j++)
        for(int t=0;t<=P;t++)
        ans=max(ans,tu[n][j][t]);
    cout<<ans;
    return 0;
}
