//水平运动时设x方向运动,若有x向风速x_windspeed
//如果反向，则功率变为 level_power*(x_windspeed+level_speed)/level_speed
//如果同向，则功率变为 level_power*(x_windspeed-level_speed)/level_speed
//如果斜向运动，则功率为   level_power*（level_speed/1.414+x_windspeed+level_speed/1.414+y_windspeed)/level_speed
//如果垂直向上  功率为    level_power*(vertical_speed+z_windspeed)/level_speed+mg*vertical_speed
//如果垂直向下  功率为    ma*vertical_speed-level_power*(vertical_speed-z_windspeed)/level_speed

#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
const int width = 100;                //格子宽度100米
const int maxn = 100;                 //大小限制
const int actions[]={-2,-1,0,1,2};    //运动，-2表示沿着无人机方向逆时针旋转90度运动，以此类推
const int directions[]={0,1,2,3};     //方向，上右下左；
const int dr[]={-1,0,1,0};
const int dc[]={0,1,0,-1};
const double rate = 0.5;
const double greedy = 0.6;
int r_start,c_start,h_start,direction_start;           //初始状态
int r,c,h,direction;               //无人机当前状态
int r_end,c_end;                         //无人机目标点位
double energy_consu;                //当前能量消耗
int n;                             //地图尺寸

double Q[maxn][maxn][4][5];            //状态是x,y,direction,走下一步；
bool vis[maxn][maxn];

class Environment{
	private:
	double altitude_map[100][100];   //地势图
	double temperature;              //温度，影响总能量
	double r_windspeed;              //x向风力
	double c_windspeed;              //y向风力
	double z_windspeed;              //z向风力
	public:
    friend double get_level_consu(int action,Environment &envir1);
    friend double move_t(int action,Environment &envir1);
    void get_map(){
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                cin>>altitude_map[i][j];
    }
    double get_altitude(int i,int j){
        return altitude_map[i][j];
    }
};

class UAV{                            //无人机类
    private:
    double energy;                    //总能量    145512J             145512/80.84=1800;  
    double level_power;               //无风情况下平飞功率 80.84       1
    double weight;                    //无人机重量  0.6kg;
    double level_speed;               //平飞速度  15m/s
    double vertical_speed;            //垂直速度  6m/s
    double max_altitude;              //最大飞行高度  1000m
    double min_altitude;              //最小飞行高度  10m
    int max_turn=2;                //飞机最大转向角，规定为90°
    public:
    UAV(){
        energy=1800.0;        level_power=1.0;  weight=0.6;
        level_speed=15.0;     vertical_speed=6.0;
        max_altitude=1000.0;  min_altitude=10.0;
    }
    friend double move_t(int action,Environment &envir1);
};
UAV flight;
bool inside(int r,int c){
    return r>=0&&r<n&&c>=0&&c<n;
}
void try_set(){
    srand(time(0));
    memset(Q,0,sizeof(Q));
}
double get_later_Qmax(){
    double s=-10000000;
    for(int i=0;i<5;++i)
        s=max(s,Q[r][c][direction][i]);
    return s;
}
void try_init(){
    r=r_start;
    c=c_start;
    h=h_start;
    direction=direction_start;
}
double get_diatance(int action){         //得到相近格子间距离
		if(action==0||action==2||action==-2)     //上下前运动
            return width;
        else
            return 1.414*width;         //斜向运动
}	
/*double get_level_consu(int direction,Environment &envir1){
    if(direction==0){

    }
}*/
// rewart=100/t;
double move_t(int action,Environment &envir1){
    double t=get_diatance(action)/flight.level_speed;
    int r_before=r,c_before=c,direction_before=direction;
    if(action==2||action==-2||action==0){
        direction=(direction+action/2+4)%4;
        r+=dr[direction];
        c+=dc[direction];
    }
    else{
        if(dc[direction]){
            c+=dc[direction];
            r=(action*dc[direction])>0?r+1:r-1;
        }
        else{
            r+=dr[direction];
            c=(action*dr[direction])>0?c-1:c+1;
        }
    }
    if(!inside(r,c)){
        r=r_before;
        c=c_before;
        direction=direction_before;
        return -1000;
    }
  // energy_consu+=get_level_consu(direction,envir1);
    double temp=get_later_Qmax();
    if(h>envir1.get_altitude(r,c)){
        t=t;
    }
    else{
        t+=(envir1.get_altitude(r,c)-h)/flight.vertical_speed;
        h=envir1.get_altitude(r,c);
    }
    t=-t;
    return rate*(t+temp);
}
void show_result(Environment &envir1){
    try_init();  
/*    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j){
            cout<<i<<j<<endl;
            for(int k=0;k<4;++k)
            for(int o=0;o<5;++o)
            cout<<Q[i][j][k][o]<<" ";
            cout<<endl;
        }*/
   while(r!=r_end||c!=c_end){
        double maxx=-10000000.0;
        int op;
        for(int i=0;i<5;++i)
            maxx=max(maxx,Q[r][c][direction][i]);
        for(int i=0;i<5;++i)
            if(maxx==Q[r][c][direction][i])
                op=i;
        move_t(actions[op],envir1);
        vis[r][c]=true;
    }
    vis[r_start][c_start]=true;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            if(vis[i][j])
            cout<<"1";
            else
            cout<<"0";
            cout<<"   ";
        }
        cout<<endl;
    }
  
}

int main(){
    Environment envir1;
    cout<<"请输入地图数组的尺寸（每一格代表100m*100m）:\n";
    cin>>n;
    cout<<"请输入无人机初始状态：x坐标，y坐标,h高度，以及朝向\n";
    cin>>r_start>>c_start>>h_start>>direction_start;
    cout<<"请上输入无人机目标点位\n";
    cin>>r_end>>c_end;
    cout<<"现在请从左到右，从上到下，输入每个地图格的高度\n";
    // envir1.get_map();
    try_set();
    try_init();
    int episode=0;
    while(episode<5000){
        try_init();
        episode++;
        int j=0;
        while(j<100000){
            j++;
            int op;
            int r_before=r,c_before=c,direction_before=direction;
            if(rand()%101>greedy)
                op=rand()%5;
            else{
                double maxx=-10000000.0;
                for(int i=0;i<5;++i)
                    maxx=max(maxx,Q[r][c][direction][i]);
                for(int i=0;i<5;++i)
                    if(maxx==Q[r][c][direction][i])
                        op=i;
            }
            double reward=move_t(actions[op],envir1);
            Q[r_before][c_before][direction_before][op]=reward+(1-rate)*Q[r_before][c_before][direction_before][op];

            if(r==r_end&&c==c_end){
                Q[r_before][c_before][direction_before][op]+=20;
                cout<<episode<<" "<<j<<" "<<r_before<<" "<<c_before<<" "<<direction_before<<" "<<actions[op]<<" "<<Q[r_before][c_before][direction_before][op]<<endl;
                break;
            }  
        }
    }
    show_result(envir1);
    cout<<"finish\n";
    return 0;
}