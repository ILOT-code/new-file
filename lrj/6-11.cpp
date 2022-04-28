#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 1024 + 10;
const int len = 32;
char s[maxn];
int buf[len][len], cnt;
void draw(char*s, int &p, int row, int col, int w) {
    char ch = s[p++];
    if (ch == 'p') {
        draw(s, p, row,    col + w / 2, w / 2);
        draw(s, p, row,    col,    w / 2);
        draw(s, p, row + w / 2, col,    w / 2);
        draw(s, p, row + w / 2, col + w / 2, w / 2);
    }
    else if (ch == 'f') {
        for (int i = row; i < row + w; i++)
            for (int j = col; j < col + w; j++)
                if (!buf[i][j]) {buf[i][j] = 1; cnt++;}
    }
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        memset(buf, 0, sizeof(buf));
        cnt = 0;
        for (int i = 0; i < 2; i++) {
            cin >> s;
            int p = 0;
            draw(s, p, 0, 0, len);
        }
        cout << cnt << endl;
    }
    return 0;
}