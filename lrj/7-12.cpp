#include<cstdio>
#include<algorithm>
using namespace std;
/*
      00    01
      02    03
04 05 06 07 08 09 10
      11    12
13 14 15 16 17 18 19
      20    21
      22    23
*/
int line[8][7] = {
    {0, 2, 6, 11, 15, 20, 22},
    {1, 3, 8, 12, 17, 21, 23},
    {10, 9, 8, 7, 6, 5, 4},
    {19, 18, 17, 16, 15, 14, 13},
};
const int rev[8] = {5, 4, 7, 6, 1, 0, 3, 2};
const int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};
int a[24];
char ans[1000];
void move(int n) {
    int temp = a[line[n][0]];
    for (int i = 0; i < 6; ++i)    a[line[n][i]] = a[line[n][i + 1]];
    a[line[n][6]] = temp;
}
bool i_final() {
    for (int i = 1; i < 8; ++i)
        if (a[center[i]] != a[center[0]])  return false;
    return true;
}
int diff(int target) {
    int cnt = 0;
    for (int i = 0; i < 8; ++i)  if (a[center[i]] != target) cnt++;
    return cnt;
}
int h() {
    return min(min(diff(1), diff(2)), diff(3));
}
bool dfs(int d, int maxd) {
    if (d + h() > maxd)  return false;
    if (i_final()) {
        ans[d] = 0;
        printf("%s\n", ans);
        return true;
    }
    for (int i = 0; i < 8; ++i) {
        move(i);
        ans[d] = 'A' + i;
        if (dfs(d + 1, maxd))  return true;
        move(rev[i]);
    }
    return false;
}
int main() {
    for (int i = 4; i < 8; ++i)
        for (int j = 0; j < 7; ++j)  line[i][j] = line[rev[i]][6 - j];
    while (scanf("%d", &a[0]) && a[0]) {
        for (int i = 1; i < 24; ++i)  scanf("%d", &a[i]);
        for (int maxd = 0;; maxd++)
            if (dfs(0, maxd))  break;
        printf("%d\n", a[6]);
    }
    return 0;
}
//1 1 1 1 3 2 3 2 3 1 3 2 2 3 1 2 2 2 3 1 2 1 3 3