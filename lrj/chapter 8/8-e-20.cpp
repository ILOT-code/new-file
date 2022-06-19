#include<cstdio>
using namespace std;

const int maxn = 505;
int T, n, a[maxn];

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        int cnt = 0;
        for (int i = 0; i < n - 1; i++) 
            for (int j = i + 1; j < n; j++) 
                if (a[i] > a[j]) cnt++;
        if (cnt % 2 && n % 2) printf("impossible\n");
        else printf("possible\n");
    }
    return 0;
}