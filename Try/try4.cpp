#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;


int check(int *a, int x, int y, int v) {
    int m;
    while (x < y) {
        m = x + (y - x) / 2;
        if (a[m] <= v) x = m + 1;
        else y = m;
    }
    return x;
}
int check2(int *a, int x, int y, int v) {
    int m;
    while (x < y) {
        m = x + (y - x) / 2;
        if (a[m] >= v) y = m;
        else x = m + 1;
    }
    return x;
}
int main() {
    int a[5] = {1, 2, 3, 4, 5};
    printf("%d\n", check(a, 0, 5, 2));
    printf("%d\n", upper_bound(a, a + 5, 2) - a);
    printf("%d\n", lower_bound(a, a + 5, 2) - a);
    printf("%d", check2(a, 0, 5, 2));
}