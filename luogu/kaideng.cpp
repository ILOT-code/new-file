//https://www.luogu.com.cn/problem/P2962
#include<cstdio>
#include<cstring>
#include<algorithm>
#include <map>
using namespace std;
int n,m,ans=100000000;
long long a[40];
map<long long,int>f;
int main()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;++i)
        a[i]=((long long)1<<i);
    for(int i=0;i<m;++i){
        int q,w;
        scanf("%d %d",&q,&w);
        --q;--w;
        a[q]|=((long long)1<<w);
        a[w]|=((long long)1<<q);
    }
    for(int i=0;i<(1<<(n/2));++i){
        int cnt=0;
        long long t=0;
        for(int j=0;j<n/2;++j){
            if((i>>j)&1){
                t^=a[j];
                ++cnt;
        }
      }
      if(!f.count(t))
        f[t]=cnt;
      else f[t]=min(f[t],cnt);
    }
    for(int i=0;i<(1<<(n-n/2));++i){
        int cnt=0;
        long long t=0;
        for(int j=0;j<(n-n/2);++j){
            if((i>>j)&1){
                t^=a[n/2+j];
                ++cnt;
            }
        }
        if(f.count((((long long)1<<n)-1)^t))
            ans=min(ans,cnt+f[(((long long)1<<n)-1)^t]);
    }
    printf("%d",ans);
    return 0;
}

