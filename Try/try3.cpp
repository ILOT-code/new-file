#include <iostream>
using namespace std;
int A[]={1,2,34,5}, B[]={22,-27,53,30,-38,-54};
int C[]={42,56,-37,-75,-10,-6}, D[]={-16,30,77,-46,62,45};

int head[10],nex[1000];
int insert(int x,int flag){
    int cnt=0;
    int y=x%11;
    int u=head[y];
    while(u){
        if(u==x) cnt++;
        u=nex[u];
    }
    if(flag){             //flag为1，执行插入；
        nex[x]=head[y];
        head[y]=x;
    }
    return cnt;
}
int main(){
    for(int i=0;i<5;++i)
        for(int j=0;j<6;++j)
           { int t=insert(A[i]+B[j],1);
            cout<<t<<" "<<i<<j<<endl;}
    int ans=0;
    for(int i=0;i<6;++i)
        for(int j=0;j<6;++j)
            ans+=insert(-C[i]-D[j],0);
    cout<<ans<<endl;
    return 0;


}