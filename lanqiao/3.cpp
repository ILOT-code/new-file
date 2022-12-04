#include<cstdio>
#include<cmath>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

int V;
vector<int> st;

int judge(int a, int b, int c) {
	return abs(a - b) + abs(a - c) + abs(b - c);
}
int solve() {
	int a = 1, b = 1, c = 1, minx = 0x3f3f3f3f;
	a = st[st.size() - 1], b = st[st.size() - 2], c = V / a / b;
	int bb = b, cc = c;
	for (int i = 0; i < st.size() - 2; ++i) {
		if (minx > judge(a, b, c)) {
			minx = judge(a, b, c);
			bb = b, cc = c;
		}
		b *= st[i], c /= st[i];
	}
	return 2 * (a * bb + a * cc + bb * cc);

}
int main() {
	scanf("%d", &V);
	int t = V;
	for (int i = 2; i * i <= V; ++i) {
		while (t % i == 0) t /= i, st.push_back(i);
	}
	if (t > 1) st.push_back(t);

	if (st.size() == 0) { printf("6"); return 0;}
	if (st.size() == 1) { printf("%d", 4 * st[0] + 2); return 0;}
	if (st.size() == 2) { printf("%d", 2 * (st[0]*st[1] + st[0] + st[1])); return 0;}
	printf("%d",solve());
	return 0;
}