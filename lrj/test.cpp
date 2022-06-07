#include<iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=10005,maxc=1005,INF=0x3f3f3f3f;
int n,c1,c2,a,b,dp[maxn][4];


//dp[u][0]为覆盖子树，且向上覆盖长度为0，就是u不放，u的子节点只能放c1
// dp[u][1]为覆盖子树，且向上覆盖长度为1，就是在u放置c1，或者在u的子节点放c2
// dp[u][2]为覆盖子树，且向上覆盖长度为2，也就是在u放置c2
// dp[u][3]为u的儿子节点为根的子树被全部覆盖，但是u和它的儿子之间的边可能没被完全覆盖（就是说父节点上有c2，所以不需要）
// [3]是为了处理  1-2-3-4-5-6-7-8-9，c1=10,c2=15这种极端的，只要c2覆盖3和7，就能覆盖所有的边
// 覆盖以u为节点的子树的最小代价
vector<int> graph[maxn];

void dfs(int u,int fa){
    dp[u][0]=0;
    dp[u][1]=c1;
    dp[u][2]=c2;
    dp[u][3]=0;
    if(graph[u].empty()) return;
    int optimal=INF,total=0;
    for(auto iter=graph[u].begin();iter!=graph[u].end();++iter){  //遍历子节点
        int v=*iter;
        if(v==fa) continue;
        dfs(v,u);
        int t=min(dp[v][0],min(dp[v][1],dp[v][2]));
        dp[u][0]+=dp[v][1];    //u的子节点v是1，u才能是0（向上覆盖长度0），不能有2，否则就会向上覆盖
        dp[u][1]+=t;  //向上覆盖长度是1，有两种选择： 1.在u上放置c1，v上1，2，3随意 2.u上不放，在一个v上放置c2，然后其他的v上随意，
        dp[u][2]+=min(t,dp[v][3]);  //u放置了c2，子节点v处于什么状态（0，1，2，3）都行
        dp[u][3]+=t;    //因为是状态3，所以u和v之间的边被它的父节点覆盖，所以v不受上面影响，可以当作一个单独的树看待
        optimal=min(optimal,dp[v][2]-t);  //其中一个v上放置c2，选择增加费用最小的一个v
    }
    total=optimal+dp[u][3];
    dp[u][1]=min(dp[u][1],total);
}

int main(void){
    while(cin>>n>>c1>>c2 && n){
//        memset(dp,INF,sizeof(dp));
        for(int i=1;i<=n;++i) graph[i].clear();
        for(int i=1;i<n;++i){
            scanf("%d%d",&a,&b);
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        dfs(1,-1);
        printf("%d\n",min(dp[1][0],min(dp[1][0],dp[1][1])));
    }
}



