#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;
class Time{
private:
	int hour,minute,second;
public:
	Time(int a,int b,int c){
		hour=a;
		minute=b;
		second=c;
	}
	void operator+=(const Time &t1){
		int pos1,pos2;
		pos1=(second+t1.second)/60;
		second=(second+t1.second)%60;
		pos2=(minute+t1.minute+pos1)/60;
		minute=(minute+t1.minute+pos1)%60;
		hour=(hour+t1.hour+pos2)%24;
	}
	void operator-=(const Time &t2){
		int pos1=0,pos2=0;
		if (second>=t2.second     )     second-=t2.second;
		else { pos1=1;                  second=second+60-t2.second;}
		if (minute-pos1>=t2.minute)     minute=minute-pos1-t2.minute;
		else { pos2=1;                  minute=minute-pos1+60-t2.minute;} 
		if (hour-pos2>=t2.hour    )     hour=hour-pos2-t2.hour;
		else {                          hour=hour-pos2+24-t2.hour;}
	}
	Time& operator++(){
		Time t0(0,0,1);
		*this+=t0;
		return *this;
	}
	Time& operator++(int){
		static Time tt(*this),t0(0,0,1);
		*this+=t0;
		return tt;
	}
	Time& operator--(){
		Time t0(0,0,1);
		*this-=t0;
		return *this;
	}
	Time& operator--(int){
		static Time tt(*this),t0(0,0,1);
		*this-=t0;
		return tt;
	}
	friend ostream& operator<<(ostream& output,const Time &p){
		output<<setfill('0')<<setw(2)<<p.hour<<':'<<setfill('0')<<setw(2)<<p.minute<<':'<<setfill('0')<<setw(2)<<p.second<<endl;
		return output;
	}
};
int main(){
	int a,b,c,a1,b1,c1;
	scanf("%d%d%d%d%d%d",&a,&b,&c,&a1,&b1,&c1);
	Time t1(a,b,c),t2(a1,b1,c1);
	t1+=(t2++);     cout<<t1;
	t1-=t2;         cout<<t1;
	++t2;           cout<<t2;
	t2+=(t1--);     cout<<t2;
	--t1;           cout<<t1;
	t2-=t1;         cout<<t2;   
	return 0;
}
	
