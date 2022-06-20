#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 50000;
int n, phi[maxn + 1], phi_psum[maxn + 1];

void phi_table(int n) {
    phi[1] = 0;
    for (int i = 2; i <= n; i++) if (!phi[i])
            for (int j = i; j <= n; j += i) {
                if (phi[j] == 0) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
}

int main() {
    phi_table(maxn);
    for (int i = 1; i <= maxn; i++)
        phi_psum[i] = phi_psum[i - 1] + phi[i];
    while (~scanf("%d", &n) && n)
        printf("%d\n", 2 * phi_psum[n] + 1);
    return 0;
}
