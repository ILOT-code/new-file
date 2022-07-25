//若k/i=p,k%i=q;则k/(i+1)=p等价于q>=p;
//并且，若k/i==k/(i+1)，则余数是等差的，q'=q-p;
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;

int main() {
    int n, k;
    while (~scanf("%d%d", &n, &k)) {
        int i = 1;
        long long ans = 0;
        while (i <= n) {
            int q = k % i, p = k / i;
            int cnt = n - i;
            if (p > 0) cnt = min(cnt, q / p);
            ans += 1LL * (2 * q - cnt * p) * (cnt + 1) / 2;
            i += cnt + 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
