#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

int main(){
	for(int i =2 ;i >= 0; --i){
		priority_queue<int> q;
		q.push(i); q.push(i+1);
		printf("%d \n", q.top());
	}

	return 0;
}