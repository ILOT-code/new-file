#include<cstdio>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;

int main() {
	string s, t;
	int T;
	scanf("%d", &T);
	for (int i = 1; i <= T; ++i) {
		cin >> s >> t;
		int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;
		for (int j = 9; j < s.size(); ++i) {
			if (s[j] == '0' && t[j] == '1') cnt1++;
			if (s[j] == '1' && t[j] == '0') cnt2++;
			if (s[j] == '?' && t[j] == '1') cnt3++;
			if (s[j] == '?' && t[j] == '0') cnt4++;
		}
		printf("Case %d: ", i);
		if (cnt3 + cnt1 < cnt2) printf("%d\n", -1);
		else printf("%d\n", cnt3 + cnt4 + max(cnt1, cnt2));
	}
	return 0;
}