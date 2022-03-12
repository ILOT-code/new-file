#include<iostream>
#include<cstring>
using namespace std;
int main(){
	class cal{
		int date1,date2;
	public:
		void set_num(int a,int b){
			date1=a;date2=b;
		}
		void run(char s){
			if(s=='+') cout<<date1+date2<<endl;
			if(s=='-') cout<<date1-date2<<endl;
			if(s=='*') cout<<date1*date2<<endl;
			if(s=='/'){
				if(date1%date2) printf("%.2lf",(double)date1/date2);
				else           printf("%d",date1/date2);
			}
		}
	};
	cal a;
	int x,y;
	char s;
	scanf("%d%d",&x,&y);
	getchar();
	s=getchar();
	a.set_num(x,y);
	a.run(s);
	return 0;
}


