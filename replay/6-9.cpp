#include <iostream>
using namespace std;
bool dfs(int &w) {
    int wl,wr,dl,dr;
    cin>>wl>>dl>>wr>>dr;
    bool b1=true, b2=true;
    if(wl==0)  b1=dfs(wl);
    if(wr==0)  b2=dfs(wr);
    w=wl+wr;
    return b1&&b2&&(wl*dl==wr*dr);
}
int main() {
    int T,w;
    cin>>T;
    while(T--) {
        if(dfs(w)) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}