#include<cstdio>
#include<vector>
using namespace std;

const int maxn = 1024 + 5;
char table[maxn][maxn];

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i++) scanf("%s", table[i] + 1);
        vector<int> win, lose;
        for (int i = 2; i <= n; ++i)
            if (table[1][i] == '1') win.push_back(i);
            else lose.push_back(i);

        int nt = n;
        while (nt > 1) {
            vector<int> win2, lose2, final;
            for (int i = 0; i < lose.size(); ++i) {
                bool match = false;
                for (int j = 0; j < win.size(); ++j)
                    if (win[j] > 0 && table[win[j]][lose[i]] == '1') {
                        printf("%d %d\n", win[j], lose[i]);
                        win2.push_back(win[j]);
                        win[j] = 0;
                        match = true;
                        break;
                    }
                if (!match) final.push_back(lose[i]);
            }

            bool first = true;
            for (int i = 0; i < win.size(); ++i)
                if (win[i]) {
                    if (first) { printf("1 %d\n", win[i]); first = false;}
                    else final.push_back(win[i]);
                }

            for (int i = 0; i < final.size(); i += 2) {
                printf("%d %d\n", final[i], final[i + 1]);
                int keep = final[i];
                if (table[final[i + 1]][keep] == '1') keep = final[i + 1];
                if (table[1][keep] == '1') win2.push_back(keep);
                else lose2.push_back(keep);
            }
            win = win2;
            lose = lose2;
            nt >>= 1;
        }
    }
    return 0;
}
