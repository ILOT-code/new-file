#include <iostream>
using namespace std;
struct Point{
    int x,y;
    int id;
    bool flag;     //flag=1是巨人
    bool operator<(const Point &a) const{
        if(y!=a.y)  return y<a.y;
        else        return x<a.x;
    }
}points[100];

double drgree(Point A,Point a){
    return (A.y-a.y)/(A.x-a.x);
}
void dfs(int L,int R){
    if(R-L==1)
    cout<<"("<<points[L].id<<","<<points[R].id<<")"<<endl;
    sort(points+L,points+R);
}
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;++i)
        cin>>points[i].flag>>points[i].x>>points[i].y;
    for(int i=0;i<n;++i)
        points[i].id=i+1;
    
}