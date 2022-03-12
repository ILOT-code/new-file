#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>
using namespace std;
#define INF 1000000000
//typedef __int64 LL;
struct node {
    int num[7], has, th, step;
};
bool vis[51111][12][7];
char s1[10], s2[10];
vector<node > save;
int ha[10], T[10];
int get(int num[]) {
    int ret = 0;
    for(int i = 0; i < 6; i++) {
        ret *= 6; ret += num[i];
    }
    return ret;
}
void change(node &in, int ii) {
    if(ii == 0) {//left move
        if(in.th) in.th --;
    }
    else if(ii == 1) {//right move
        if(in.th != 5) in.th ++;
        if(in.th == 5) {
            if(in.has <= 4) in.has += 5;
        }
        else {
            if(in.has <=4 && in.th > in.has) in.has ++;
            if(in.has >=5 && in.th > in.has - 5) in.has ++;
        }
    }
    else if(ii == 2) { //left swap
        swap(in.num[0], in.num[in.th]);
    }
    else if(ii == 3) {//right swap
        swap(in.num[5], in.num[in.th]);
        if(in.has < 5) in.has += 5;
    }
    in.step ++;
}
void bfs() {
    queue< node > Q;
    save.clear();
    memset(vis, 0, sizeof(vis));
    node now, next;
    for(int i = 0; i < 6; i++) now.num[i] = i;
    now.has = 0;  now.th = 0; now.step = 0;
    vis[get(now.num)][now.has][now.th] = 1;
    Q.push(now);
    while(!Q.empty()) {
        now = Q.front(); Q.pop();
        save.push_back(now);
        for(int i = 0; i < 4; i++) {
            next = now;
            change(next, i);
            int tmp = get(next.num);
            if(vis[tmp][next.has][next.th]) continue;
            vis[tmp][next.has][next.th] = 1;
            Q.push(next);
        }
    }
}
void sol() {
    int ret = INF;
    for(int i = 0; i < save.size(); i++) {
        int flag = 0,sum = 0;
        int tt = save[i].has;
        if(tt > 4) tt -= 5;
        for(int j= 0; j < 6; j++) {
            int dd = 0;
            if(j <= 4 && j <= tt)  dd = 1;
            else if(j == 5 && save[i].has >= 5) dd = 1;
            int pre = save[i].num[j];
            if(dd == 1 )  sum += abs(s1[pre] - s2[j]) ;
            else if(dd == 0 && s1[pre] != s2[j]) {
                flag = 1; break;
            }
        }
        if(!flag) ret = min(ret, save[i].step + sum);
    }
    printf("%d\n", ret);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif // ONLINE_JUDGE
    bfs();
    while(scanf("%s%s", s1, s2) != EOF) {
        for(int i = 0; i < 6; i++) s1[i] -= '0', s2[i] -= '0';
        sol();
    }
    return 0;
}
