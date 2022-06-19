#include <iostream>
using namespace std;
const int maxd = 2000 + 5;
int sum[maxd];
int ll = 1000, rr = 1000;
void build (int p) {
    int value;
    cin >> value;
    if (value == -1)  return;
    if (ll > p)   ll = p;
    if (rr < p)   rr = p;
    sum[p] += value;
    build(p - 1); build(p + 1);
}
int main() {
    build(1000);
    for (int i = ll; i <= rr; ++i)
        cout << sum[i] << ' ';
    return 0;
}
