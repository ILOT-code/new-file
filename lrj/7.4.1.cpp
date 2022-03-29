#include <iostream>
using namespace std;
int tot,n;
int c[100];
void search(int cur){
    if(cur==n)  tot++;
    else for(int i=0;i<n;++i){
        c[cur]=i;
        int ok=1;
        for(int j=0;j<cur;++j){
            if(c[j]==c[cur]||c[j]-j==c[cur]-cur||c[j]+j==c[cur]+cur){
                ok=0;
                break;
            }
        }
        if(ok)  search(cur+1);
    }
}
int main(){
    cin>>n;
    search(0);
    cout<<tot;
    return 0;
}