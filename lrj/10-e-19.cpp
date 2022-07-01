#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const double g = 9.81;
double k, l, s, w;

int main() {
	while (cin >> k >> l >> s >> w) {
		if (k == 0 && l == 0 && s == 0 && w == 0) break;
		if (l >= s) {
			double s_v = 2 * g * s;
			if (s_v > 100) cout << "Killed by the impact.\n";
			else cout << "James Bond survives.\n";
		}
		else {
			double s_v1 = 2 * g * l;
			double s_v2 = s_v1 - k * (s - l) * (s - l) / w + 2 * g * (s - l);
			if (s_v2 < 0) cout << "Stuck in the air.\n";
			else if (s_v2 > 100) cout << "Killed by the impact.\n";
			else cout << "James Bond survives.\n";
		}
	}
	return 0;
}