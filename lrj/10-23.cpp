#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

struct BIGNUM {
    static const int  maxlen = 100 + 5;
    int num[maxlen], len;

    BIGNUM() {memset(num, 0, sizeof(num)); len = 1;}
    BIGNUM(int rhs) {
        len = 0; memset(num, 0, sizeof(num));
        while (rhs) {
            num[len++] = rhs % 10;
            rhs /= 10;
        }
    }

    BIGNUM(const char *s) {
        len = strlen(s); memset(num, 0, sizeof(num));
        for (int i = 0; i < len; ++i)
            num[i] = s[len - 1 - i] - '0';
    }

    friend istream& operator>>(istream& in, BIGNUM &rhs) {
        char s[maxlen];
        in >> s; rhs = s;
        return in;
    }

    friend ostream& operator<<(ostream& out, const BIGNUM &rhs) {
        for (int i = rhs.len - 1; i >= 0; --i) printf("%d", rhs.num[i]);
        return out;
    }

    BIGNUM operator+(const BIGNUM& rhs) {
        BIGNUM c;
        int biglen = max(len, rhs.len);
        int i;
        for (i = 0; i < biglen; ++i) {
            c.num[i] += num[i] + rhs.num[i];
            if (c.num[i] >= 10) {
                c.num[i + 1] += c.num[i] / 10;
                c.num[i] %= 10;
            }
        }
        c.len = i + (c.num[i] != 0);
        return c;
    }

    BIGNUM operator-(const BIGNUM& rhs) { //只能执行大数减小数
        BIGNUM c;
        for (int i = 0; i < len; ++i) {
            c.num[i] += num[i] - rhs.num[i];
            if (c.num[i] != 0) c.len = i + 1;
            if (c.num[i] < 0) {
                c.num[i] += 10;
                c.num[i + 1] -= 1;
            }
        }
        return c;
    }

    BIGNUM operator*(const BIGNUM& rhs) {
        BIGNUM c;
        if ((len == 1 && num[0] == 0) || (rhs.len == 1 && rhs.num[0] == 0)) return c;
        for (int i = 0; i < len; ++i)
            for (int j = 0; j < rhs.len; ++j) {
                c.num[i + j] += num[i] * rhs.num[j];
                if (c.num[i + j] >= 10) {
                    c.num[i + j + 1] += c.num[i + j] / 10;
                    c.num[i + j] %= 10;
                }
            }
        c.len = len + rhs.len - (c.num[len + rhs.len - 1] == 0);
        return c;
    }
    bool cansub(const BIGNUM& a, const BIGNUM& b, int a1) {
        if (a.num[a1 + b.len] != 0) return true;
        for (int i = b.len - 1; i >= 0; --i) {
            if (a.num[a1 + i] > b.num[i]) return true;
            if (a.num[a1 + i] < b.num[i]) return false;
        }
        return true;
    }
    BIGNUM operator/(const BIGNUM& rhs) { //得到商
        BIGNUM c, t = *this;
        //if (rhs.len == 1 && rhs.num[0] == 0) return c;
        for (int i = len - rhs.len; i >= 0 ; --i)
            while (cansub(t, rhs, i)) {
                for (int j = 0; j < rhs.len; ++j) {
                    t.num[i + j] -= rhs.num[j];
                    if (t.num[i + j] < 0) {
                        t.num[i + j] += 10;
                        t.num[i + j + 1] -= 1;
                    }
                }
                c.num[i]++; c.len = max(i + 1, c.len);
            }
        return c;
    }
};

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        BIGNUM n;
        cin >> n;
        cout << n*(n - 1) / 2 + n*(n - 1)*(n - 2)*(n - 3) / 24 + 1 << endl;
    }
    return 0;
}