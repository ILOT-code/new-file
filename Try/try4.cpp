#include<iostream>
using namespace std;

int main()
{
	class Person
{
    int age_;

  public:
    void SetAge(int age)
    {
        this->age_ = age;
    }
    friend ostream& operator<<(ostream &stream, const Person &p)
    {
        stream << p.age_ << endl;
        return stream;
    }
};
    Person a;
    a.SetAge(10);
    cout << a << endl;
}
