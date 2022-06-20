#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 10;
char s[maxn];

int main() {
    while (~scanf("%s", s)) {
        int a = 0, b = 0, n = strlen(s);
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                b++;
                if (s[(i + 1) % n] == '0') a++;
            }
        }
        if (a * n == b * b) printf("EQUAL\n");
        else if (a * n > b * b) printf("SHOOT\n");
        else printf("ROTATE\n");
    }
    return 0;
}
