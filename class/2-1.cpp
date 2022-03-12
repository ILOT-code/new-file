#include <cstdio>
using namespace std;
bool ss(int t)
{
    bool flag=true;
    if(t==1) return false;
    for(int i=2;i*i<=t;i+=2)
        if(t%i==0)
        {
            flag=false;
            break;
        }
    return flag;
}
int main()
{
    int x,t=2;
    scanf("%d",&x);
    while(x!=1)
    {
       if(ss(t)&&x%t==0)
       {
           printf("%d ",t);
           x=x/t;
       }
       else t++;
    };
    return 0;
}

