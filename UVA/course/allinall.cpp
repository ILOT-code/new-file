#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    char s[1000],t[1000];
    scanf("%s%s",s,t);
    int slen=strlen(s);
    int tlen=strlen(t);
    int i=0,j=0;
    while(t[j]!=0)
    {
        if(s[i]==t[j++])
        i++;
    }
    if(s[i]==0)
        cout<<1<<endl;
    else
        cout<<0<<endl;
    cout<<slen<<endl;
    cout<<tlen<<endl;
    return 0;
}
