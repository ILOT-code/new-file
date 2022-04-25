#include <iostream>
using namespace std;
int n,L;
char s[100];
int num;
bool dfs(int cur){
    if(num++==n){
        for(int i=0;i<cur;++i)
            cout<<s[i]<<" ";
        return true;
    }
    for(int i=0;i<L;++i){
        s[cur]=i+'A';
        int ok=1;
        for(int j=1;2*j<=cur+1;++j){
            int equal=1;
            for(int k=0;k<j;++k)
                if(s[cur-k]!=s[cur-k-j]){
                    equal=0;
                    break;
                }
            if(equal){
                ok=0;
                break;
            }
        }
        if(ok&&dfs(cur+1))  return true;
    }
    return false;

}
int main(){
    cin>>n>>L;
    dfs(0);
    return 0;
}