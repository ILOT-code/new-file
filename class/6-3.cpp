#include <iostream>
using namespace std;
class vehicle{
    private:
    int speed,mount,weight;
    public:
    vehicle(int speed=0,int mount=0,int weight=0):speed(speed),mount(mount),weight(weight){}
    virtual void display(){
        cout<<"vehicle messgae\n";
    }
    int get_speed(){
        return speed;
    }
    int get_mount(){
        return mount;
    }
    int get_weight(){
        return weight;
    }
};
class car:public vehicle{
    private:
    int capacity;
    public:
    car(int speed=0,int mount=0,int weight=0,int capacity=0):
                vehicle(speed,mount,weight),capacity(capacity){}
    virtual void display(){
        cout<<"car message\n";
        cout<<get_speed()<<" "<<get_mount()<<" "<<get_weight()<<" "<<capacity<<endl;
    }
};
class truck:public vehicle{
    private:
    int load;
    public:
    truck(int speed=0,int mount=0,int weight=0,int load=0):
                vehicle(speed,mount,weight),load(load){}
    virtual void display(){
        cout<<"truck message\n";
        cout<<get_speed()<<" "<<get_mount()<<" "<<get_weight()<<" "<<load<<endl;
    }
};
class boat:public vehicle{
    private:
    char s;
    public:
    boat(int speed=0,int mount=0,int weight=0,char s='k'):
                vehicle(speed,mount,weight),s(s){}
    virtual void display(){
        cout<<"boat message\n";
        cout<<get_speed()<<" "<<get_mount()<<" "<<get_weight()<<" "<<s<<endl;
    }
};
void fun(vehicle &p){
    p.display();
}
int main(){
    car   c(80,4,1000,4);
    truck t(80,4,2500,3000);
    boat  b(30,0,12000);
    fun(c);
    fun(t);
    fun(b);
    return 0;
}