//https://www.luogu.com.cn/problem/P1706
#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;
int pd[11],b[11],n;
void dfs(int step)
{
    if(step==n+1)
        {for(int i=1;i<=n;i++) cout<<setw(5)<<b[i];cout<<endl;return;}
    for(int i=1;i<=n;i++)
        if(!pd[i])
        {
            b[step]=i;
            pd[i]=1;
            dfs(step+1);
            pd[i]=0;
        }
        return;
}
int main()
{
    cin>>n;
    memset(pd,0,sizeof(pd));
    dfs(1);
    return 0;
}
