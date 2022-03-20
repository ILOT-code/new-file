#include <cstdio>
using namespace std;
const int maxn = 100;
int tu[maxn][maxn], vis[maxn], too[maxn],t,n,m,ok=1;
bool dfs(int x){
    vis[x]=-1;
    for(int i=0;i<n;++i){
        if(tu[x][i]){
            if(vis[i]==-1) return false;
            if(!vis[i]&&!dfs(i)) return false; 
        }  
    }
    too[t--]=x;
    vis[x]=1;
    return true;
}
int main(){
    scanf("%d%d",&n,&m);
    t=n-1;
    for(int i = 0;i < m;++i){
        int u, v;
        scanf("%d%d",&u,&v);
        tu[u][v]=1;
    }
    for(int i = 0;i< n;++i)
    if(!vis[i])
    if(!dfs(i))
    ok=0;
    if(ok){
    for(int i = 0;i < n;++i)
    printf("%d",too[i]);
    }
    else printf("wrong");
    return 0;

}