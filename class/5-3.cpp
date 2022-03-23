#include <iostream>
using namespace std;
class Person{
    public:
    char *name;
    int age,female;
    Person(){
        cout<<"Parameterless constructor\n";
    }
    Person(char *s,int age,int female):name(s),age(age),female(female){
        cout<<"Parameter constructor\n";
    }
    Person(const Person &a):name(a.name),age(a.age),female(a.female){
        cout<<"Copy constructor\n";
    }
    void display(){
        cout<<"Information:\n";
        cout<<"Name: "<<name<<"    "<<"Sex: ";
        if(female)  cout<<"female    ";
        else        cout<<"male    ";
        cout<<"Age: "<<age<<endl;
    }
};
int main(){
    char s[10];
    int age,female;
    cin>>s>>female>>age;
    Person P1;
    P1.name=s; P1.age=age; P1.female=female;
    P1.display();
    cin>>s>>female>>age;
    Person P2(s,age,female);
    P2.display();
    Person P3=P2;
    P3.display();
    return 0;
}