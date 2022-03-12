//http://poj.org/problem?id=1183
#include<iostream>
using namespace std;
int main()
{
    long long a,A,t;
    cin>>a;
    A=a*a+1;
    t=a;
    while(A%t)
        t--;
    cout<<t+A/t+2*a;
    return 0;
}
