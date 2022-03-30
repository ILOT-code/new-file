#include <cstdio>
#include <cstring>
#include <queue>
#include <cctype>
using namespace std;
const int maxs=20;
const int maxn=200;
int dx[]={-1,0,1,0,0};
int dy[]={0,1,0,-1,0};
int deg[maxn],G[maxn][5];
int d[maxn][maxn][maxn];
int s[3],t[3];
int ID(int a,int b,int c){
    return(a<<16)|(b<<8)|c;
}

int main(){
    int w,h,n;
    while(scanf("%d%d%d",&w,&h,&n)==3){
        char maze[maxs][maxs];
        int id[maxn][maxn],x[maxn],y[maxn],cnt=0;
        memset(deg,1,sizeof(deg));
        for(int i=0;i<w;++i)
            for(int j=0;j<h;++j){
                scanf("%c",maze[i][j]);
                char c=maze[i][j];
                if(c!='#'){
                    id[i][j]=cnt;
                    x[cnt]=i;
                    y[cnt]=j;
                    G[cnt][4]=cnt;
                    if(islower(c))  s[c-'a']=cnt;
                    if(isupper(c))  t[c-'A']=cnt;
                    if(j>=1&&maze[i][j-1]==' '){
                        G[cnt][3]=cnt-1;
                        G[cnt-1][1]=cnt;
                        deg[cnt]++;
                        deg[cnt-1]++;
                    }
                    if(i>=1&&maze[i-1][j]==' '){
                        G[cnt][0]==id[i-1][j];
                        G[id[i-1][j]][2]=cnt;
                        deg[cnt]++;
                        deg[id[i-1][j]]++;
                    }  
                }
                cnt++;
            }
        if(n<=2) {deg[cnt]=1;G[cnt][4]=cnt;s[2]=t[2]=cnt++;};
        if(n<=1) {deg[cnt]=1;G[cnt][4]=cnt;s[1]=t[1]=cnt++;};
        printf("%d\n",bfs());
    }
    return 0;
}