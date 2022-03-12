#include <iostream>
#include <cstring>
using namespace std;
int main(){
	class ecg{
	private:
		int c;
		double f;
	public:
		void set_value(int t)
		{
			c=t;f=c*9/5.0+32;
		}
		void put_out()
		{
			printf("%.1lf",f);
		}
	};
	int t;
	ecg a;
	cin>>t;
	a.set_value(t);
	a.put_out();
	return 0;
}

	







		
