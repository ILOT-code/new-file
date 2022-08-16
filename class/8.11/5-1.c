#include<stdio.h>
#include<string.h>
double fun(int n) {
   if (n == 0) return 1.0;
   if (n > 0) return 10.0 * fun(n - 1);
   else return 0.1 * fun(n + 1);
}

int main() {
   double num, move, ans;
   scanf("%lfe%lf", &num, &move);
   ans = num * fun(move);
   printf("%f", ans);
}
