#include <cstdio>
#include <cstring>
using namespace std;
int a[10];
int n;
int h(){
    int count=0;
    for(int i=0;i<n-1;++i)  if(a[i+1]!=1+a[i]) count++;
    if(a[n-1]!=n) count++;
    return count;
}
bool dfs(int d,int maxd){
    if(3*d+h()>3*maxd)  return false;
    if(h()==0)  return true;
    int b[10],olda[10];
    memcpy(olda,a,sizeof(a));
    for(int i=0;i<n;++i)
        for(int j=i;j<n;++j){
            int cnt=0;
            for(int k=0;k<n;++k)   
             if(k<i||k>j)  b[cnt++]=a[k];
            for(int k=0;k<=cnt;++k){
                int cnt2=0;
                for(int p=0;p<k;++p)    a[cnt2++]=b[p];
                for(int p=i;p<=j;++p)   a[cnt2++]=olda[p];
                for(int p=k;p<cnt;++p)  a[cnt2++]=b[p];
                if(dfs(d+1,maxd))   return true;
                memcpy(a, olda, sizeof(a));
            }
        }
    return false;
}
int solve(){
    if(h()==0)  return 0;
    for(int i=1;i<9;++i)
        if(dfs(0,i))    return i;
    return 9;
}
int main(){
    int kase=0;
    while(scanf("%d",&n)){
        for(int i=0;i<n;++i)    scanf("%d",&a[i]);
        printf("Case %d: %d\n", ++kase, solve());
    }
}