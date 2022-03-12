#include <iostream>
using namespace std;
typedef struct{
    int a[2],b[2];
}rectangle;
int calculate(int x1,int x2,int x3,int x4){
    if(x3<x1)        return calculate(x3,x4,x1,x2);
    if(x3>=x2)       return 0;
    return min(x4,x2)-x3;
}
int main(){
    rectangle a,b;
    cin>>a.a[0]>>a.a[1]>>a.b[0]>>a.b[1];
    cin>>b.a[0]>>b.a[1]>>b.b[0]>>b.b[1];
    cout<<calculate(a.a[0],a.b[0],b.a[0],b.b[0])*calculate(a.b[1],a.a[1],b.b[1],b.a[1]);
    return 0;
}