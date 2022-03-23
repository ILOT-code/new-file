#include <iostream>
#include <cstdio>
using namespace std;
class Rectangle{
    private:
    double m_length,m_width;
    public:
    double Perimeter(){
        return 2*(m_length+m_width);
    }
    double Area(){
        return m_length*m_width;
    }
    void SetWidth(double w){
        m_width=w;
    }
    double GetWidth(){
        return m_width;
    }
    void SetLength(double l){
        m_length=l;
    }
    double GetLength(){
        return m_length;
    }
    void SetRange(){
        if(m_length<20.0&&m_width<20.0)
            cout<<"length and width are both in 0.0 - 20.0\n";
        else if(m_length>=20.0&&m_width>=20.0)
            cout<<"length and width are not both in 0.0 - 20.0\n";
        else if(m_length>=20.0)
            cout<<"length is not in 0.0 - 20.0\n";
        else 
            cout<<"width is not in 0.0 - 20.0\n";
    }
};
int main(){
    double a,b;
    cin>>a>>b;
    Rectangle t;
    t.SetLength(a);
    t.SetWidth(b);
    cout<<"Length: "<<t.GetLength()<<"    "<<"Width: "<<t.GetWidth()<<endl;
    t.SetRange();
    cout<<"Perimeter: "<<t.Perimeter()<<endl;
    cout<<"Area: "<<t.Area()<<endl;
    return 0;
}