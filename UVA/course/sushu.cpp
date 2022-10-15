#include <iostream>
#include <cmath>
using namespace std;
void pp(int n);
int ss(int t);
int main()
{
    int n;
    cin>>n;
    pp(n);
    return 0;
}
void pp(int n)
{
    int i;
    if (n>1)
    {
    for(i=2;i<=n;i++)
    {
        if(ss(i)&&n%i==0)
            {
                cout<<i<<endl;
                break;
            }
    }pp(n/i);}

    else cout<<"finish";

}
int ss(int t)
{
    int i,flag=0;
    float g=sqrt(t);
    for (i=2;i<g;i++)
    {
        if(t%i==0) break;
    }
    if(i>g) flag++;
    return flag;
}
