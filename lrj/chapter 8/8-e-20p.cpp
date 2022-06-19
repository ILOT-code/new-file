#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef int State[8];
State st[40400], goal, start[30];
bool vis1[10], vis2[40400];
int fact[8];
int cnt = 0;

void init_fact() {
	fact[0] = 1;
	for (int i = 1; i < 8; ++i) fact[i] = fact[i - 1] * i;
}
bool try_insert(int s) {
	int code = 0;
	for (int i = 0; i < 8; ++i) {
		int count = 0;
		for (int j = i + 1; j < 8; ++j) if (st[s][j] < st[s][i]) count++;
		code += fact[7 - i] * count;
	}
	if (vis2[code]) return 0;
	return vis2[code] = 1;
}
void to_start(int k) {
	if (k == 8) {
		start[cnt][0] = 1; start[cnt][1] = 2; start[cnt][2] = 3; start[cnt][3] = 4;
		for (int i = 4; i < 8; ++i) {
			if (start[cnt][i] == 0) start[cnt][i] = start[cnt - 1][i];
			else break;
		}
		cnt++;
		return;
	}
	for (int i = 5; i <= 8; ++i)
		if (vis1[i] == 0) {
			start[cnt][k] = i;
			vis1[i] = 1;
			to_start(k + 1);
			vis1[i] = 0;
		}
}

bool judge(int x) {
	int t = 0;
	for (int i = 0; i < 8; ++i)
		for (int j = i + 1; j < 8; ++j)
			if (start[x][i] > start[x][j]) t++;
	return !(t & 1);
}
void caozuo(int i, int j) {
	swap(st[i][j], st[i][j + 3]);
	swap(st[i][j + 1], st[i][j + 2]);
}

int main() {
	to_start(4);
	init_fact();
	goal[0] = 1; goal[1] = 2; goal[2] = 3; goal[3] = 4; goal[4] = 5; goal[5] = 6; goal[6] = 7; goal[7] = 8;
	bool flag1 = 1, flag2 = 0;
	for (int i = 0; i < cnt; ++i) if (judge(i)) {
		printf("%d ", i);
		memset(vis2, 0, sizeof(vis2));
		int front = 0, rear = 1;
		memcpy(st[0], start[i], sizeof(st[0]));
		while (front < rear) {
			State& s = st[front];
			if (memcmp(goal, s, sizeof(s)) == 0) {flag2 = 1; break;}
			for (int j = 0; j < 5; ++j) {
				State& t = st[rear];
				memcpy(t, s, sizeof(s));
				caozuo(rear, j);
				if (try_insert(rear)) rear++;
			}
			front++;
		}
		if (flag2) {flag2 = 0; printf("yes\n") ; continue;}
		else {flag1 = 0; printf("no\n"); break;}
	}
	printf("%d", flag1);
	return 0;
}