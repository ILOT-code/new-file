/** 搜索树的深度最多为9，并不大，因此不设置最深深度，以比赛结束的局面为叶子结点。
 *  在此程序中，人先手，执'-',AI执‘+’，后手。flag = 1代表AI落子。
 */
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 362880 + 10;

int cnt, x, y; //x,y是下一步下子的位置。 cnt表示搜索的结点位置。
struct State { //定义棋盘局面
  int a[3][3], score, free; //数组a表示棋盘落子情况，0：未下，1：AI落子，-1：人落子.score表示评分，free表示可落子数。
  bool flag;//表示下一步是谁下子，1AI，0人。
  State(bool f = 0) {
    memset(a, 0, sizeof(a));
    score = 0; free = 9;
    flag = f;
  }
} states[maxn]; //为搜素的结点提前分配空间，cnt代表当前位置。

int h(State& now) { //对局面进行评分，未结束0，平局0，AI胜利1，人胜利-1.
  for (int i = 0; i < 3; ++i)
    if (now.a[i][0] != 0 && now.a[i][0] == now.a[i][1] && now.a[i][0] == now.a[i][2]) return now.score = now.a[i][0];
    else if (now.a[0][i] != 0 && now.a[0][i] == now.a[1][i] && now.a[0][i] == now.a[2][i]) return now.score = now.a[0][i];
  if (now.a[1][1] != 0 && ((now.a[0][0] == now.a[1][1] && now.a[0][0] == now.a[2][2])
                           || (now.a[0][2] == now.a[1][1] && now.a[0][2] == now.a[2][0]))) return now.score = now.a[1][1];
  return now.score = 0;
}

char trans(int color) { //把棋盘上的子转化成规定的'+'或'-'.
  if (color == 1) return '+';
  if (color == -1) return '-';
  else return ' ';
}
void draw(State& now) { //把局面画出来
  for (int i = 0; i < 3; ++i)
    printf("%c|%c|%c\n", trans(now.a[i][0]), trans(now.a[i][1]), trans(now.a[i][2]));
}

void move(State& now, int i, int j) { //当前局面now,在落子在(i,j)后转化成的局面。
  now.a[i][j] = now.flag == 1 ? 1 : -1; //下子
  now.free -= 1; //可落子数减1
  now.flag ^= 1; //换手
  now.score = h(now); //计算局面分数
}

State luozi(State& now) { //落子，在人或AI选择好了下子位置后，执行落子函数
  while (x < 0 || x > 2 || y < 0 || y > 2 || now.a[x][y] != 0) { //越界或重复的子不被接受
    printf("落子不被接受，请重新选择！\n");
    scanf("%d%d", &x, &y);
  }
  move(now, x, y);
  return now;
}

int alpha_beta(int u, int alph, int beta, bool is_max) { //剪枝，u表示当前结点，is_max表示该节点是否是AI选择.
  if (states[u].score != 0 || states[u].free == 0) return states[u].score;//叶子结点，直接返回score.
  if (is_max) { //若是AI选择
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j) if (states[u].a[i][j] == 0) { //遍历可落子位置
          int d = ++cnt;            //创建新结点
          states[d] = states[u];
          move(states[d], i, j);     //新结点有states[u]转移而来
          alph = max(alph, alpha_beta(d, alph, beta, is_max ^ 1)); //更新alph值
          if (alph >= beta) break; //触发剪枝
        }
    return alph;
  } else {  //人选择
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j) if (states[u].a[i][j] == 0) {
          int d = ++cnt;           //创建新结点
          states[d] = states[u];
          move(states[d], i, j);  //新结点有states[u]转移而来
          beta = min(beta, alpha_beta(d, alph, beta, is_max ^ 1)); //更新beta值
          if (alph >= beta) break; //触发减枝
        }
    return beta;
  }
}
void AI(State now) { //AI进行决策
  int slect = -INF;  //子局面的最佳值，初始化未无穷小
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)if (now.a[i][j] == 0) {
        cnt = 0;
        states[0] = now;
        move(states[0], i, j);
        int t = alpha_beta(0, -INF, INF, 0);
        if (t > slect) { //更新最佳值
          slect = t;
          x = i, y = j; //选择最佳值对应的坐标
        }
      }
}

int main() {
  State game;
  draw(game);
  while (game.free > 0) {
    if (game.flag == 0) {printf("请您下子：\n"), scanf("%d%d", &x, &y);} //人落子
    else {printf("AI落子为:\n"), AI(game);} //AI落子
    game = luozi(game);
    draw(game);
    if (game.score == 1) {printf("+胜利\n"); break;}
    if (game.score == -1) {printf("-胜利\n"); break;}
  }
  if (game.score == 0) printf("平局\n");
  return 0;
}
