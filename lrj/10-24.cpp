#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;
int h, w;
char s[maxn];

int main() {
    while (~scanf("%d%d", &h, &w)) {
        int ans = 0, c = 0;
        for (int i = 0; i < h; ++i) {
            scanf("%s", s);
            for (int j = 0; j < w; ++j) {
                if (s[j] == '/' || s[j] == '\\') c++;
                else if (c % 2) ans++;
            }
        }
        printf("%d\n", ans + c / 2);
    }
    return 0;
}
