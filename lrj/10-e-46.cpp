#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long LL;

int T, N, K;
LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }
struct Frac {
    LL p, q, l;
    Frac() {}
    Frac(LL p1, LL q1, LL l1) {
        LL z = gcd(p1, q1);
        p = p1 / z, q = q1 / z, l = l1;
    }
    bool operator < (const Frac &x) const {
        return p * x.q < q * x.p;
    }
};
priority_queue<Frac> ans;

void print(Frac x) {
    LL z = gcd(x.p, x.q);
    x.p /= z, x.q /= z;
    printf("%lld/%lld\n", x.p, x.q);
}

Frac Ans() {
    for (int i = 1; i < K; i++) {
        LL l = ans.top().l, p = ans.top().p, q = ans.top().q;
        ans.pop();
        p *= (l - 1), q *= l;
        ans.push(Frac(p, q, l));
    }
    return ans.top();
}

int main() {
    scanf("%d", &T);
    while (T--) {
        while (!ans.empty()) ans.pop();
        scanf("%d%d", &N, &K);
        for (int i = 1; i <= N; ++i) {
            LL l, t;
            scanf("%lld%lld", &l, &t);
            ans.push(Frac(t, l, l));
        }
        print(Ans());
    }
    return 0;
}