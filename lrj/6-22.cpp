//accepted
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn=1000+5;
const double w=1000.0;
int n,vis[maxn];
double left,right;
double x[maxn],y[maxn],r[maxn];
bool insert(int u,int v){
    return (x[u]-x[v])*(x[u]-x[v])+(y[u]-y[v])*(y[u]-y[v])<=(r[u]+r[v])*(r[u]+r[v]);
}
bool dfs(int u){
    vis[u]=1;
    if(y[u]-r[u]<0)   return true;
    for(int v=0;v<n;++v)
        if(!vis[v]&&insert(u,v)&&dfs(v))    return true;
    if(x[u]<r[u])
        left=min(left,y[u]-sqrt(r[u]*r[u]-x[u]*x[u]));
    if(x[u]+r[u]>w)
        right=min(right,y[u]-sqrt(r[u]*r[u]-(w-x[u])*(w-x[u])));
    return false;
}
int main(){
    while(scanf("%d",&n)==1){
        for(int i=0;i<n;++i)
            scanf("%lf%lf%lf",&x[i],&y[i],&r[i]);
        memset(vis,0,sizeof(vis));
        left=right=w;
        bool ok=true;
        for(int i=0;i<n;++i)
            if(!vis[i]&&y[i]+r[i]>=w&&dfs(i)){
                ok=false;
                break;
            }
        if(ok)  printf("0.00 %.2lf %.2lf %.2lf\n",left,w,right);
        else    printf("IMPOSSIBLE\n");   
    }
    return 0;
}
