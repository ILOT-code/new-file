#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
int read()
{
	char op = getchar(); int x = 0, f = 1;
	while (op < 48 || op > 57) {if (op == '-') f = -1; op = getchar();}
	while (48 <= op && op <= 57) x = (x << 1) + (x << 3) + (op ^ 48), op = getchar();
	return x * f;
}
const int k = 1 << 24;
int nxt[15][10], g[k + 10];
bool vis[k + 10];
int pre[k + 10], button[k + 10]; //分别表示：从哪个状态过来；从那个状态过来是使用什么按钮
struct node
{
	int st; //状态
	int f;
	node(int zltqwq) //变量起 @zltqwq 是因为想不到好名字了。膜拜 zlt
	{
		int h = 0;
		st = zltqwq;
		for (int i = 0; i < 12; i++) h += (4 - ((st >> (i * 2)) & 3)) & 3;
		h /= 2;
		f = g[st] + h;
	}
	friend bool operator <(node y, node x) {return x.f < y.f;}
};
int IAKIOI; //初始状态
void Astar()
{	int cnt = 0;
	priority_queue <node> q;
	q.push(node(IAKIOI)), vis[IAKIOI] = true;
	while (!q.empty())
	{
		int s = q.top().st;
		q.pop();
		if (s == 0) break; //等同于全是1
		for (int i = 0; i < 12; i++)
		{
			int os = (s >> (i * 2)) & 3, op = nxt[i][os], ops = (s >> (op * 2)) & 3;
			int ds = s ^ (os << (i * 2)) ^ (ops << (op * 2));
			ds = ds | (((os + 1) & 3) << (i * 2)) | (((ops + 1) & 3) << (op * 2));
			if (cnt < 20) {cnt++; printf("%d\n", ds);};
			if (vis[ds]) continue;
			g[ds] = g[s] + 1, vis[ds] = true;
			pre[ds] = s, button[ds] = i + 1;
			q.push(node(ds));
		}
	}
}
void input()
{
	for (int i = 0; i < 12; i++)
	{
		int a = read() - 1;
		IAKIOI |= a << (i * 2);
		for (int j = 0; j < 4; j++) nxt[i][j] = read() - 1;
	}
}
void output(int x)
{
	if (x == IAKIOI) return;
	output(pre[x]), printf("%d ", button[x]);
}
int main()
{
	input();
	Astar();
	printf("%d\n", g[0]); //0是最终状态
	output(0);
	return 0;
}