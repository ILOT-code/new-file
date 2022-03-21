#include <cstdio>
using namespace std;
int main(){
  for(int i = 0; i <10; ++i){
        int couple = 2 * (i/2) + !(i%2);
        printf("%d",couple);
}
return 0;
}