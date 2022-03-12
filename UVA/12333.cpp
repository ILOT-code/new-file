#include <iostream>
using namespace std;
int get_num(int x){
    int cout=0;
    do{
        x/=10;
        cout++;
    }while(x);
    return cout;
}
int q_pow(int x){
    if(x==0) return 1;
    return 10*q_pow(x-1);
}
int main(){
    int a=1,b=1,i=0,flag=0,ii=3;
    char s[40+5];
    gets(s);
    while(s[i]){i++;};
    for(;ii<=100000;++ii){
        int t,num;
        t=b;b=a+b;a=t;
        num=get_num(b);
        if(num>=i){
            int j=1,tem=b;
            for(;j<=i;++j){
                int com;
                com=tem/q_pow(num-j);
                tem%=q_pow(num-j);
                if(s[j-1]-'0'!=com) break;
            }
            if(j==i+1) flag=1;
        }
        if(flag) break;
    }
    if(flag) cout<<ii-1;
    return 0;
}