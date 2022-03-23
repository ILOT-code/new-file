//析构函数出错
#include <iostream>
#include <algorithm>
using namespace std;
class List{
    private:
    int *a;
    int length;
    public:
    List(){
        a=new int[6];
        length=0;
    }
    List(const List &L){
        for(int i=0;i<6;++i)
            a[i]=L.find(i);
        length=L.length;
    }
    void input(){
        for(int i=0;i<5;++i)
            cin>>a[i];
        length=5;
    }
    void insert(int i=8){
        a[length]=i;
        length++;
    }
    void display(){
        sort(a,a+length);
        for(int i=0;i<length;++i)
            cout<<a[i]<<" ";
        cout<<endl;
    }
    int find(int i)const{
        return a[i];
    }
};
int main(){
    List a,b;
    a.input();
    a.display();
    a.insert();
    a.display();
    b=a;
    b.display();
    return 0;
}