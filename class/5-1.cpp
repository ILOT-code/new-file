#include <iostream>
#include <iomanip>
using namespace std;
int id(char s){return s-'0';}
bool big_m(int m){return m==1||m==3||m==5||m==7||m==8||m==10||m==12;}
bool fulld(int run,int m,int d){
    if(big_m(m)&&d==31)             return true;
    if(m==2&&d==28+run)             return true;
    if(!big_m(m)&&m!=2&&d==30)      return true;
    else                            return false;
}
class Data{
    private:
    int y,m,d;
    bool flag=1;
    public:
    Data(char *s){
        y=id(s[0])*1000+id(s[1])*100+id(s[2])*10+id(s[3]);
        m=id(s[4])*10+id(s[5]);
        d=id(s[6])*10+id(s[7]);
    }
    void out(){
        if(flag){
             cout<<setfill('0')<<setw(4)<<y<<setw(2)<<m<<setw(2)<<d<<endl;
        }
        else cout<<"out of limitation!";
    }
    void change(int n);
};
void Data::change(int n){
    for(int i=0;i<n;++i){
        int run=!(y%400)||(!(y%4)&&(y%100));
        fulld(run,m,d)?(d=1,m++):(d++);
        if(m==13) {m=1;y++;}
        if(y==10000){flag=0;break;}
    }
}
int main(){
    char s[9];
    int n;
    cin>>s>>n;
    Data a(s);
    a.change(n);
    a.out();
    return 0;
}