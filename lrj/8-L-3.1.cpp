#include <iostream>
using namespace std;
int a[2048][2048];

void dfs(int k, int x, int y) {
    if (k == 1) {
        a[x][y] = 1;
        a[x][y + 1] = 2;
        a[x + 1][y] = 2;
        a[x + 1][y + 1] = 1;
        return;
    }
    k = k - 1;
    dfs(k, x, y);
    for (int i = 0; i < 1 << k; ++i)
        for (int j = 0; j < 1 << k; ++j) {
            a[i][j + (1 << k)] = a[i][j] + (1 << k);
            a[i + (1 << k)][j] = a[i][j] + (1 << k);
            a[i + (1 << k)][j + (1 << k)] = a[i][j];
        }
}

int main() {
    int k;
    cin >> k;
    dfs(k, 0, 0);
    for (int i = 0; i < 1 << k; ++i) {
        for (int j = 0; j < 1 << k; ++j)
            cout << a[i][j] << " ";
        cout << endl;
    }
    return 0;
}