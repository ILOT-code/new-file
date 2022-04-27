#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e5+5;
const int inf=1e9;
int t,n,d,ans,pos[maxn],a[maxn],st2[maxn][30],st1[maxn][30],Log[maxn];
void init(){
    Log[1] = 0;//预处理log函数
    for(int i = 2;i <= n+1;i++) 
        Log[i] = Log[i/2]+1;
    for(int i = 1;i <= n;i++)
         st1[i][0] = st2[i][0] = a[i];
    for(int j = 1; (1<<j) <= n;j++){ //涉及到位运算多加括号!
        for(int i = 1;i + (1<<(j-1)) <= n;i++){
            st1[i][j] = max(st1[i][j-1],st1[i+(1<<(j-1))][j-1]);
            st2[i][j] = min(st2[i][j-1],st2[i+(1<<(j-1))][j-1]);
        }
    }
}
int ask1(int l,int r){
    int k = Log[r-l+1];
    int mx = max(st1[l][k],st1[r-(1<<k)+1][k]);
    return mx;
} 
int ask2(int l,int r){
    int k = Log[r-l+1];
    int mx = min(st2[l][k],st2[r-(1<<k)+1][k]);
    return mx;
} 
bool check(){
    init();
    for(int i=1;i<=n;i++){
        for(int j=i+3;j<=n;j++){
                int t1=ask1(i,j);
                int t2=ask2(i,j);
                if(a[i]>a[j]&&pos[t1]>pos[t2])return 1;
                if(a[i]<a[j]&&pos[t1]<pos[t2])return 1;
        }
    }
    return 0;
}
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            pos[a[i]]=i;
        }
        if(check())printf("YES\n");
        else printf("NO\n");
    }
}

