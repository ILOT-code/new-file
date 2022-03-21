//实际上，多出的本不存在边并不会影响原图中环的存在性，因此可以忽略它们，把标记用的d数组省略掉；
//另外 输入格式并不正确，可以简化；
//ID 与 couple 可以简化；
#include <cstdio>
using namespace std;
const int maxn = 52;
const int maxd = 40000+10;
int G[maxn][maxn];
int d[maxn][maxd];
int vis[maxn];
int ID(char *s){
    int n = s[0]-'A';
    if(s[1]=='+') return 2*n;
    if(s[1]=='-') return 2*n+1;
    else         return -1;
}
bool dfs(int u){
    vis[u]=-1;
    for(int v = 0; v < maxn; ++v)
    if(G[u][v])
    if(vis[v] == -1 || (!vis[v] && !dfs(v))) return false;
    vis[u] = 1;
    return true;
}
int main() {
    int T;
    scanf("%d",&T);
    for(int i = 0; i < T; ++i){
        char s[4][3];
        scanf("%s%s%s%s",s[0],s[1],s[2],s[3]);
        for(int j = 0; j < 4; ++j){
            int id = ID(s[j]);
            if(id < 0)     continue;
            d[id][i]++;
        }
    }
    for(int i = 0; i < maxn; ++i){
        bool ok=false;
        for(int j = 0; j < T; ++j)
            if(d[i][j]) {ok=true;break;}
        if(!ok)    continue;
        int couple = 2 * (i/2) + !(i%2);
        for(int j = 0; j < T; ++j){
            if(!d[couple][j])    continue;
            for(int k = 0; k < maxn; ++k)
                if(d[k][j] && k != couple)
                    G[i][k]=1;
                else if(k == couple)
                    G[i][k]=d[k][j]-1?1:0;
        }
    }
    int ok1=true;
    for(int i = 0; i < maxn; ++i)
        if(!vis[i]&&!dfs(i)) {ok1=false;break;}
    if(!ok1) printf("YES\n");
    else printf("NO\n");
    return 0;
}