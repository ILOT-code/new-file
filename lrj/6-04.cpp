#include <cstdio>
using namespace std;
const int maxn = 100000 + 5;
int last, cur, next[maxn];
char s[maxn];
int main() {
    while (scanf("%s", s + 1) == 1) {
        int n = 0;
        while (s[1 + n])n++;
        for (int i = 1; i <= n; ++i) {
            if (s[i] == '[')  cur = 0;
            else if (s[i] == ']')  cur = last;
            else {
                next[i] = next[cur];
                next[cur] = i;
                if (cur == last) last = i;
                cur = i;
            }
        }
        for (int i = next[0]; i != 0; i = next[i])
            printf("%c", s[i]);
        printf("\n");
    }
    return 0;
}