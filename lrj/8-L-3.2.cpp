#include <iostream>
using namespace std;
int a[1024][1024];
int ans;
void dfs(int k,int x,int y,int x0,int y0){
    if(k==1){
        ans++;
        return;
    }
    k--; ans++;
    int xx=x0/(1<<k), yy=y0/(1<<k);
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j){
            int xs=x+i*(1<<k), ys=y+j*(1<<k);
            if(i==xx&&j==yy)
                dfs(k,xs,ys,x0,y0);
            else  dfs(k,xs,ys,xs+(!i)*((1<<k)-1),ys+(!j)*((1<<k)-1));
        }
}
int main(){
    int k,x0,y0;
    cin>>k>>x0>>y0;
    a[x0][y0]=1;
    dfs(k,0,0,x0,y0);
    cout<<ans;
    return 0;

}