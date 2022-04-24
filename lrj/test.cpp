#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 112345;
int a[MAXN], id[MAXN], n;

bool cmp(int x, int y) {
    return a[x] > a[y];
}

int main() {
    while (~scanf("%d", &n)) {
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            sum += a[i];
            id[i] = i;
        }
        if (sum & 1) { puts("No"); continue; }

        sort(id, id + n, cmp);
        sum >>= 1;
        for (int i = 0; i < n; ++i) {
            int t = id[i];
            if (a[t] <= sum) {
                sum -= a[t];
                a[t] = 1;
            }
            else a[t] = -1;
        }
        printf("Yes\n");
        for (int i = 0; i < n; ++i) printf("%d ", a[i]);
        printf("\n");
    }
    return 0;
}