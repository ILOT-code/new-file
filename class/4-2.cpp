#include <iostream>
#include <algorithm>
using namespace std;
struct stu{
    string name;
    int a,b,c;
};
bool com( struct stu a,struct stu b){
    if(a.a+a.b+a.c!=b.a+b.b+b.c) return a.a+a.b+a.c>b.a+b.b+b.c;
    if(a.a!=b.a)                 return a.a>b.a;
    if(a.b!=b.b)                 return a.b>b.b;
    else                         return a.name<b.name;
}
int main(){
    struct stu a[1024+5];
    int N,k;
    cin>>N;
    for(int i=1;i<=N;++i){ cin>>a[i].name>>a[i].a>>a[i].b>>a[i].c;}
    cin>>k;
    sort(a+1,a+1+N,com);
    cout<<a[k].name<<' '<<a[k].a+a[k].b+a[k].c;
    return 0;
      
}