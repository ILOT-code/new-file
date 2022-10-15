#include <iostream>
using namespace std;
int main()
{
    int n,a[100],i,s=0,i0;
    cin>>n;
    for(i=2;s<=n;i++)
    {
        a[i]=i;
        s+=i;
    }
    i0=i=i-2;
    int h=n-(s-i-1);
    for(;h>0;h--)
    {
       a[i--]++;
       if(i==1)
        i=i0;
    }
    for(i=2;i<i0+1;i++)
        cout<<a[i]<<endl;
        cout<<i0;
    return 0;
}
