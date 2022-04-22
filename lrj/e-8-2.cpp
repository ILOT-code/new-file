#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
char ans[1000];

int main()
{
    int n;
    while (scanf("%d", &n) == 1 && n) {
        string s[n];
        for (int i = 0; i < n; i++) cin >> s[i];
        sort(s, s + n);
        string left = s[n / 2 - 1], right = s[n / 2];

        int length = min(left.size(), right.size());
        int i = 0;
        for (; i < length ; ++i) {
            ans[i] = left[i];
            if (left[i] == right[i] && i == length - 1) break;
            if (left[i] == right[i]) continue;
            else break;
        }
        if (i + 1 < left.size()) {
            if (left[i] < right[i] - 1) ans[i] = left[i] + 1;
            else {
                if (i == right.size() - 1) {
                    while (i != left.size() - 1 && left[i + 1] == 'Z') {i++; ans[i] = left[i];}
                    if (i < left.size() - 1) {
                        i++;
                        if (i == left.size() - 1) ans[i] = left[i];
                        else ans[i] = left[i] + 1;
                    }
                }
                if (i < right.size() - 1) ans[i] = left[i] + 1;
            }
        }
        for (int j = 0; j <= i; ++j)
            printf("%c", ans[j]);
        printf("\n");
    }
    return 0;
}