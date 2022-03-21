#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 52;
int G[maxn][maxn];
int vis[maxn];
int  ID(char a, char b){
    return (a-'A')*2+(b=='+'?0:1);
}
void connect(char a1,char a2,char b1,char b2){
    if(a1=='0'||b1=='0')    return;
    int u=ID(a1,a2)^1; int v=ID(b1,b2);
    G[u][v]=1;
}
bool dfs(int u){
    vis[u]=-1;
    for(int v=0;v<maxn;++v) if(G[u][v])
    if(vis[v]==-1||(!vis[v]&&!dfs(v)))  return false;
    vis[u]=1;
    return true;
}
bool has_circle(){
    memset(vis,0,sizeof(vis));
    for(int i=0;i<maxn;++i)
        if(!vis[i]&&!dfs(i))    return true;
    return false;
}
int main(){
    int n;
    while(scanf("%d",&n)){
        memset(G,0,sizeof(G));
        while(n--){
            char s[10];
            scanf("%s",s);
            for(int i=0;i<4;++i)
                for(int j=0;j<4;++j)  if(i!=j)    
                    connect(s[2*i],s[2*i+1],s[2*j],s[2*j+1]);
        }
        if(has_circle())  printf("Yes\n");
        else              printf("No\n");
        }
    }
    return 0;
}