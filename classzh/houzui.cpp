#include <iostream>
#include <stack>
using namespace std;
stack<char> ope;
int id(char s){
    if(s=='#')
        return -1;
    if(s=='(')
        return 0;
    if(s=='+'||s=='-')
        return 1;
    if(s=='*'||s=='/')
        return 3;
    else
        return 5;
}
int main(){
    char s[100];
    cin>>s;
    ope.push('#');
    int i=-1;
    while(s[++i]!=0){
        if(s[i]>='0'&&s[i]<='9')
            cout<<s[i]<<" ";
        else{
            int top=id(ope.top());
            if(s[i]=='(')
                ope.push(s[i]);
            else if(s[i]==')'){
                cout<<ope.top()<<" ";
                ope.pop();
                ope.pop();
            }
            else if(id(s[i])>top)
                ope.push(s[i]);
            else{
                do{
                    cout<<ope.top()<<" ";
                    ope.pop();
                }while(id(ope.top())>=id(s[i]));
                ope.push(s[i]);
               
            }
        }
    }
    while(ope.top()!='#'){
        cout<<ope.top()<<" ";
        ope.pop();

    }
    
    return 0;
}