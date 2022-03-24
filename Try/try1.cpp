#include <iostream>
using namespace std;
const int maxn=100;
int n,vis[maxn],d[maxn];
void dfs(int u){
  if(u==n){
    for(int i=0;i<n;++i)
      printf("%d ",d[i]);
    printf("\n");
    return;
  }
  for(int i=1;i<=n;++i){
    if(!vis[i]){
      d[u]=i;
      vis[i]=1;
      dfs(u+1);
      vis[i]=0;
    }
  }
}
int main(){
  scanf("%d",&n);
  dfs(0);
}