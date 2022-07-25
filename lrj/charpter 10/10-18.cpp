#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;
int n;

LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}
LL lcm(LL a, LL b) {
    return a / gcd(a, b) * b;
}

int LL_len(LL x) {
    int len = 1;
    while (x = x / 10) len++;
    return len;
}

void put_char(int cnt, char ch) {
    while (cnt--) printf("%c", ch);
}

void output(LL a, LL b, LL c) {
    if (b == 0) printf("%lld\n", a);
    else {
        int L1 = LL_len(a);
        put_char(L1 + 1, ' '); printf("%lld\n", b);
        printf("%lld ", a); put_char(LL_len(c), '-'); printf("\n");
        put_char(L1 + 1, ' '); printf("%lld\n", c);
    }
}

int main() {
    while (~scanf("%d", &n) && n) {
        if (n == 1) {output(1, 0, 0); continue;}
        LL c = 1, b = 0;
        for (int i = 2; i <= n - 1; ++i) c = lcm(c, i);
        for (int i = 2; i <= n - 1; ++i) b += c / i;
        b *= n;
        LL g = gcd(b, c);
        b /= g; c /= g;
        LL a = 1 + n + b / c;
        b %= c;
        output(a, b, c);
    }
    return 0;
}