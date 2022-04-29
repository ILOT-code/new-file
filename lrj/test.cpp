#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
typedef int State[6];
State st[500], goal, start[30];
bool vis1[10], vis2[500];
int fact[6];
int cnt = 0;

void init_fact() {
	fact[0] = 1;
	for (int i = 1; i < 5; ++i) fact[i] = fact[i - 1] * i;
}
bool try_insert(int s) {
	int code = 0;
	for (int i = 0; i < 6; ++i) {
		int count = 0;
		for (int j = i + 1; j < 6; ++j) if (st[s][j] < st[s][i]) count++;
		code += fact[5 - i] * count;
	}
	if (vis2[code]) return 0;
	return vis2[code] = 1;
}
void to_start(int k) {
	if (k == 6) {
		start[cnt][0] = 1; start[cnt][1] = 2;
		for (int i = 2; i < 6; ++i) {
			if (start[cnt][i] == 0) start[cnt][i] = start[cnt - 1][i];
			else break;
		}
		cnt++;
		return;
	}
	for (int i = 3; i <= 6; ++i)
		if (vis1[i] == 0) {
			start[cnt][k] = i;
			vis1[i] = 1;
			to_start(k + 1);
			vis1[i] = 0;
		}
}

bool judge(int x) {
	int t = 0;
	for (int i = 0; i < 6; ++i)
		for (int j = i + 1; j < 6; ++j)
			if (start[x][i] > start[x][j]) t++;
	return !(t & 1);
}
void caozuo(int i, int j) {
	swap(st[i][j], st[i][j + 3]);
	swap(st[i][j + 1], st[i][j + 2]);
}

int main() {
	to_start(2);
	init_fact();
	goal[0] = 1; goal[1] = 2; goal[2] = 3; goal[3] = 4; goal[4] = 5; goal[5] = 6;
	bool flag1 = 0, flag2 = 0;
	for (int i = 0; i < cnt; ++i) if (judge(i)) {
			memset(vis2, 0, sizeof(vis2));
			int front = 0, rear = 1;
			for (int j = 0; j < 6; ++j) st[0][j] = start[i][j];
			while (front < rear) {
				State& s = st[front];
				if (memcmp(goal, s, sizeof(s)) == 0) {flag2 = 1; break;}
				for (int j = 0; j < 3; ++j) {
					State& t = st[rear];
					memcpy(t, s, sizeof(s));
					caozuo(rear, i);
					if (try_insert(rear)) rear++;
				}
			}
			if(flag2) {flag2 = 0; continue;}
			front++;
			if(front == rear) {flag1 = 0; break;}
		}
	printf("%d", flag1);
	return 0;
}