#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 50000 + 5;
char s[maxn];

void change(int pos, int last) {
	s[pos] = '+'; s[last] = '-';
	for (int i = pos + 1; i < last; ++i) s[i] = '0';
}

int main() {
	while (~scanf("%s", s + 1) && s[1] != '0') {
		s[0] = '0';
		int len = strlen(s + 1), last = -1, pos = len, sum = 0;
		while (pos >= 1) {
			if (s[pos] == '1') {
				sum++;
				if (last == -1) last = pos;
			} else {
				if (sum >= 2) {change(pos, last); last = pos; sum = 1;}
				else {sum = 0; last = -1; }
			}
			pos--;
		}
		if (sum > 2) change(pos, last);
		for (int i = 0; i <= len; ++i) if (s[i] == '1') s[i] = '+';
		if (s[0] == '0') puts(s+1);
		else puts(s);
	}
	return 0;
}