#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
typedef int State[10];
const int maxstate=362880+1000;
const int dr[]={-1,0,1,0};
const int dc[]={0,1,0,-1};
State start,goal;
bool vis[maxstate];
int fact[9];
void set_fact(){
    fact[0]=1;
    for(int i=1;i<9;++i)
        fact[i]=fact[i-1]*i;
}
int ID(State s){
    int code=0;
    for(int i=0;i<9;++i){
        int cnt=0;
        for(int j=i+1;j<9;++j)  if(s[j]<s[i]) cnt++;
        code+=fact[8-i]*cnt;
    }
    return code;
}
int bfs(){
    queue<int *> q;
    vis[ID(start)]=true;
    q.push(start);
 //   int t=0;
    while(!q.empty()){
  //  printf("%d\n",++t);
        State u;
        memcpy(u,q.front(),sizeof(u));
        q.pop();
        if(memcmp(goal,u,sizeof(u))==0) return u[10];
        int z;
        for(int i=0;i<9;++i)    if(!u[i])   break;
        int r=z/3, c=z%3;
        for(int i=0;i<4;++i){
            int newr=r+dr[i];
            int newc=c+dc[i];
            if(newr>=0&&newr<3&&newc>=0&&newc<3){
                int newz=3*newr+newc;
                State v;
                memcpy(v,u,sizeof(u));
                v[newz]=u[z];
                v[z]=u[newz];
                v[10]++;
                if(!vis[ID(v)]) q.push(v);
            }
        }
    }
    return -1;
}
int main(){
    for(int i=0;i<9;++i)    scanf("%d",&start[i]);
    for(int i=0;i<9;++i)    scanf("%d",&goal[i]);
    set_fact();
    printf("%d\n",bfs());
    return 0;
}
