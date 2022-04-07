#include <cstdio>
#include <stack>
using namespace std;
int main(){
    int target[20],n;
    stack<int>s;
    s.push(0);
        while(scanf("%d",&n)){
        for(int i=0;i<n;++i)  scanf("%d",&target[i]);
        int p=1,ok=1;
        for(int i=0;i<n;++i){
            if(target[i]!=s.top() && target[i]!=p){
                if(p>=n) {ok=0;break;}
                s.push(p++);
            }
            if(target[i]==s.top())  s.pop();
            if(target[i]==p)  p++;
        }
        printf("%d",ok);
    }
    return 0;
}