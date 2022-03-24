//输入格式与OJ上是不一样的；
#include<cstdio>
using namespace std;
const int maxn=1000+5;
int n,target[maxn];
int main(){
    while(scanf("%d",&n)==1){
        int a=1,b=1,ok=1;
        for(int i=1;i<=n;++i)
        scanf("%d",&target[i]);
        for(int i=1;i<=n;++i){
            if (i==target[n-a+1]) {a++;continue;}
            if (i==target[b])      {b++;continue;}
            else                   {ok=0;break;}
        }
        printf("%s\n",ok?"Yes":"No");
    }
    return 0;
}