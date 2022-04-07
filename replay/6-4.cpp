#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=1000+5;
char s[maxn];
int next[maxn];
int main(){
    while(scanf("%s",s+1)){
        int n=strlen(s+1);
        next[0]=0;
        int last=0,cur=0;
        for(int i=1;i<=n;++i){
            if(s[i]=='[')  cur=0;
            else if(s[i]==']')  cur=last;
            else{
                next[i]=next[cur];
                next[cur]=i;
                if(cur==last) last=i;
                cur=i;
            }   
        }
        for(int i=next[0];i!=0;i=next[i])
            printf("%c",s[i]);
        printf("\n");
    }
    return 0;
}