#include<cstdio>
using namespace std;
const int M=50+5;
int main()
{
    char s[M];
    int len=0;
    gets(s);
    while(s[len]) ++len;
    for(int i=0;i<len;++i)
    {
        if(s[len-1-i]-'0'==9) s[len-1-i]='0';
        else {s[len-1-i]++;break;}
    }
    if(s[0]!='0') puts(s);
    else {putchar('1');puts(s);}
    return 0;
}

