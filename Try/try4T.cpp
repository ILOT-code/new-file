#include<deque>
#include<iostream>
#include<iterator>
#include<algorithm>
using namespace std;
int main(){
    deque<int> a_line;
    a_line.push_front(1);
    a_line.push_front(2);
    a_line.push_front(3);
    a_line.push_front(1);
    deque<int>::iterator pos=a_line.begin();
    a_line.insert(pos,0);
    sort(a_line.begin(),a_line.end());
    pos--;
    for(;pos!=a_line.end();++pos)
    cout<<*pos;
    return 0;




}

