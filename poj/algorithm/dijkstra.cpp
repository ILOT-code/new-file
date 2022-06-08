//http://poj.org/problem?id=1062
#include <iostream>
#include <cstdio>
#include<cmath>
#include<cstring>
#include <algorithm>
#define inf 10000000
#define maxn 105
using namespace std;
int lim,n;
int map[maxn][maxn];
int p[maxn],l[maxn];
int d[maxn],v[maxn];
bool in_lim[maxn];
int dijkstra()
{
    memset(v,0,sizeof(v));
    for(int i=1;i<=n;i++)
        d[i]=(i==1?0:inf);
    for(int i=1;i<=n;i++)
    {
       int x=0,mini=inf;
       for(int j=1;j<=n;j++)
           if(!v[j]&&in_lim[j]&&d[j]<mini)
           {
               x=j;
               mini=d[j];
           }
       v[x]=1;
       for(int z=1;z<=n;z++)
       {
           if(in_lim[z]&&!v[z])
           d[z]=min(d[z],d[x]+map[x][z]);

       }
    }
    int m=inf;
    for(int i=1;i<=n;i++)
    {
        d[i]+=p[i];
        if(d[i]<m)
            m=d[i];
    }
    return m;
}
int main()
{
    while(scanf("%d %d",&lim,&n)==2)
    {
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)
            map[i][j]=(i==j?0:inf);
        for(int i=1;i<=n;i++)
        {
            int k;
            cin>>p[i]>>l[i]>>k;
            for(int j=1;j<=k;j++)
            {
                int t;
                cin>>t;
                cin>>map[i][t];
            }
        }
        int kinglev=l[1];
        int cost,cost_min=inf;
        for(int i=0;i<=lim;i++)
        {
            memset(in_lim,0,sizeof(in_lim));
            for(int j=1;j<=n;j++)
                if(l[j]<=kinglev+i&&l[j]>=kinglev-lim+i)
                in_lim[j]=1;
            cost=dijkstra();
            if(cost<cost_min)
                cost_min=cost;
        }
        cout<<cost_min<<endl;
    }
    return 0;
}
