#include <iostream>
using namespace std;
const double pi=3.14;
class circle{
    private:
    double r;
    public:
    circle(double r=0):r(r){}
    double area(){
        return pi*r*r;
    }
    double get_r(){
        return r;
    }
};
class Cylinder:public circle{
    private:
    double h;
    public:
    Cylinder(double r,double h):circle(r),h(h){}
    double area1(){
        return 2*area()+2*pi*get_r()*h;
    }
    double volume(){
        return area()*h;
    }
};
int main(){
    double r,h;
    cout<<"Please enter the radius of the circle:";
    cin>>r;
    cout<<"Please enter the height of the cylinder:";
    cin>>h;
    circle c(r);
    cout<<"The area of the circle is:"<<c.area()<<endl;
    Cylinder t(r,h);
    cout<<"The area of the cylinder is:"<<t.area1()<<endl;
    cout<<"The volumn of the cylinder is:"<<t.volume()<<endl;
    return 0;
}