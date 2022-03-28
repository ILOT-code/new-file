#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;
 
//宏定义，定义上下左右四个动作的代号 
#define up 0
#define down 1
#define left 2
#define right 3
 
//马尔可夫决策过程公式中的比例系数 
double rate = 0.8;
 
//走到每个位置的分数
//实际上就是存储的地图，0代表可以走，-1代表地雷，5代表终点 
int score[5][5] = {0,0,0,-1,0,
				 0,-1,0,0,0,
				 -1,0,-1,0,-1,
				 -1,0,0,0,-1,
				 0,-1,0,0,5};
//Q-table 
double Qtable[5][5][4] = {0};
 
//记录是否走过这一点，测试结果时使用 
int vis[5][5] = {0};
 
//智能体的位置， 
int x = 0;
int y = 0;
 
//是否到达终点，0不到达，1到达 
int dead = 0;
 
//贪心系数，20表示执行贪心决策的概率为20% 
int greedy = 20;
 
//全局初始化函数 
bool game_set(){
	
	//初始化Q-table，智能体不能走出边界，所以再边界上再往外走，就会得到负奖励 
	for (int i = 0; i <= 4; i++){
		Qtable[0][i][up] = -100;
		Qtable[4][i][down] = -100;
		Qtable[i][0][left] = -100;
		Qtable[i][4][right] = -100;
	}
		
	//初始化随机数种子 
	srand(time(0));
	
	return true;
}
 
//每次训练之前的变量初始化 
bool game_init(){
	//位置初始化为0，0 
	x = 0;
	y = 0;
	dead = 0;
	return true;
}
//没用的变量 
int cnt = 0;
 
//获取最大的预期奖励，对应马尔可夫决策过程 
//Qtable[x][y][i] = Qtable[x][y][i] + rate * ( reward[x1][y1] + max( Qtable[x1][y1][i] )) 
//中的 max( Qtable[x1][y1][i]） 
double get_expected_max_score(){
	double s = -10000;
	for (int i = 0; i <= 3; i++)
		s = max(s, Qtable[x][y][i]);
	return s;
	
}
 
//执行一步操作，返回执行动作后的 奖励 ，对应马尔可夫决策过程 
//Qtable[x][y][i] = Qtable[x][y][i] + rate * ( reward[x1][y1] + max( Qtable[x1][y1][i] )) 
//中的 Qtable[x][y][i] + rate * ( reward[x1][y1] + max( Qtable[x1][y1][i] )) 
 
double game_go(int dir){
	
	//记录现在所在位置 
	int xx = x, yy = y;
	
	//如果走出了边界，则奖励为0，且x，y的值不变 
	if (x == 0 && dir == up)	{return 0;}
	if (x == 4 && dir == down)	{return 0;}
	if (y == 0 && dir == left)	{return 0;}
	if (y == 4 && dir == right)	{return 0;}
	
	
	
	//走到下一步 
	if (dir == up) x--;
	if (dir == down) x++;
	if (dir == right) y++;
	if (dir == left) y--;
	
	//如果到了终点，返回到达终点的奖励 
	if (x == 4 && y == 4){
		dead = 1;
		return score[x][y];
	}
 
	//得到执行动作后的预期奖励，见函数说明 
	double tmp = get_expected_max_score();
	
	//对应马尔可夫决策过程 
	//Qtable[x][y][i] = Qtable[x][y][i] + rate * ( reward[x1][y1] + max( Qtable[x1][y1][i] ))
	//中的 reward[x1][y1] + max( Qtable[x1][y1][i] ) 
	return score[x][y] + 1.0 * rate * tmp;
	
}
 
//训练结果测试 
void game_final_test(){
	//本局游戏初始化 
	game_init();
	
	//当没有走到终点时 
	while (!(x == 4 && y == 4)){
		int op = 0;
	//选取Qtable中奖励最大的行为执行 
	double maxx = -1000000;
	for (int i = 0; i < 4; i++)
		maxx = max(maxx + 0.0, Qtable[x][y][i]);
	for (int i = 0; i < 4; i++)	
		if (maxx == Qtable[x][y][i])
			op = i;
		
		game_go(op);
		//如果走到了一个点，记录这个点的vis = 1， 方便输出观察 
		vis[x][y] = 1;
	}
	//输出，带有 @ 符号的代表智能体选择的路径 
	for (int i = 0 ; i <= 4; i++){
		for (int j = 0; j <= 4; j++){
			cout<<score[i][j];
			if (vis[i][j] == 1)
				cout<<'@';
			cout<<"    ";
		}
		cout<<endl;
	}
	
}
 
 
int main(){
	//全局初始化 
	game_set();
	
	//总共训练1000次，取决于具体训练效果 
	int episode = 1000;
	
	while(episode > 0){
		//游戏初始化 
		game_init();
		episode--;
		int j = 0;
		
		//每轮游戏走50步，走到终点或者走够50步时结束 
		while(j < 50){
			j++;
			//operation，代表下一步要执行的行为 
			int op;
			//记录现在的位置 
			int xx = x, yy = y;
			
			//一定概率下，随机选择行为 
			if (rand() % 101 > greedy){
				op = rand() % 4;
			}	
			//一定概率下，走最优解 
			else{
				int maxx = -1000000;
				for (int i = 0; i < 4; i++)
					maxx = max(maxx + 0.0, Qtable[x][y][i]);
				for (int i = 0; i < 4; i++)	
					if (maxx == Qtable[x][y][i])
						op = i;
			}
			//if (op == 0) cout<<"up"<<endl;
			//if (op == 1) cout<<"down"<<endl;
			//if (op == 2) cout<<"left"<<endl;
			//if (op == 3) cout<<"right"<<endl;	
			
			//执行行为，获取奖励 
			double reward = game_go(op);
	
			//进行马尔可夫决策过程，优化Qtable 
			Qtable[xx][yy][op] += reward / 1000;
			
			//如果到达终点，游戏结束 
			if (dead == 1)	break;
		
		
	}
		
	}
	//输出Qtable 
	for (int i = 0;i <= 4;i ++){
		for (int j = 0;j <= 4;j ++){
			for (int k = 0;k <= 3;k ++)
			cout<<Qtable[i][j][k]<<' ';
			cout<<"      ";
		}
	cout<<endl;
	}
	cout<<endl<<endl;
	
	//测试智能体最终选择的路径 
	game_final_test();
}