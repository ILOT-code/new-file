#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int T, a[9][9];

int main()
{
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < 9; i += 2)
            for (int j = 0; j <= i; j += 2)
                scanf("%d", &a[i][j]);
        for (int i = 8; i > 0; i -= 2)
            for (int j = 1; j <= i; j += 2)
                a[i][j] = (a[i - 2][j - 1] - a[i][j - 1] - a[i][j + 1]) / 2;

        for (int i = 1; i < 9; i += 2)
            for (int j = 0; j <= i; ++j)
                a[i][j] = a[i + 1][j] + a[i + 1][j + 1];

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (j) printf(" ");
                printf("%d", a[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}