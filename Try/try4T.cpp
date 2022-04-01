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

const int dr[]={-1,0,1,0};            //行随方向的变化
const int dc[]={0,1,0,-1};            //列随方向的变化
const double rate = 0.5;              //马可洛夫决策过程的比例系数，不易过大
const double greedy = 0.8;            //贪心系数
const double gamma=0.9;
int r_start,c_start,h_start,direction_start;           //初始状态
int r,c,h,direction;               //无人机当前状态
int r_end,c_end,h_end;                         //无人机目标点位
int n,m;                             //地图尺寸
double T,energy_consu;                         //全局时间 能量消耗


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
    friend void get_level_consu(int action,const Environment &envir1);
    friend double move_t(int action,Environment &envir1);
    void get_map(){
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                cin>>altitude_map[i][j];
    }
    double get_altitude(int i,int j){
        return altitude_map[i][j];
    }
    void set_end(int r,int c,double h){
        altitude_map[r][c]=h;
    }
    void add_map(int r,int c,double h){
        altitude_map[r][c]=max(altitude_map[r][c],h);
    }
};
class obstacle:public Environment{
    public:
    int count_state,count_dynamic;
    struct state_obs{
        int sr,sc;
        double altitude;
    }states[maxn];
    struct Dynamic_obs{
        int dr_start,dc_start,dr_end,dc_end;
        int r,c,h;                                      //记录修改的静态altitude_map的值，方便改回来。
        double d_altitude;
        double d_speed;
    }dynamics[10];
    friend void add_dynamic_obs(obstacle &envir1);
    friend void delete_dynamic_obs(obstacle &envir1);
    void get_obstacle(){
        cout<<"请输入静态障碍物个数：\n";
        cin>>count_state;
        for(int i=0;i<count_state;++i){
            cout<<"请输入第"<<i+1<<"个静态障碍物的行、列与高度:\n";
            cin>>states[i].sr>>states[i].sc>>states[i].altitude;
        }
        cout<<"请输入动态障碍物个数：\n";
        cin>>count_dynamic;
        for(int i=0;i<count_dynamic;++i){
            cout<<"请输入第"<<i+1<<"个动态障碍物的起始行、起始列、终点行、终点列、高度和速度：\n";
            cin>>dynamics[i].dr_start>>dynamics[i].dc_start>>dynamics[i].dr_end>>dynamics[i].dc_end>>dynamics[i].d_altitude>>dynamics[i].d_speed;
        }
    }
    void set_state_map(){
        for(int i=0;i<count_state;++i){
            int r=states[i].sr;
            int c=states[i].sc;
            double h=states[i].altitude;
            add_map(r,c,h);
        }
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
    friend void get_level_consu(int action,const Environment &envir1);
};
UAV flight;
bool inside(int r,int c){
    return r>=0&&r<n&&c>=0&&c<m;
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
    T=0;
    energy_consu=0;
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

void add_dynamic_obs(obstacle &envir1){
    for(int i=0;i<envir1.count_dynamic;++i){
        double run_r=envir1.dynamics[i].dr_end-envir1.dynamics[i].dr_start;
        double run_c=envir1.dynamics[i].dc_end-envir1.dynamics[i].dc_start;
        double run_l=sqrt(run_c*run_c+run_r*run_r);
        double dr=envir1.dynamics[i].d_speed*T*run_r/run_l;
        double dc=envir1.dynamics[i].d_speed*T*run_c/run_l;
        int ddr=(int)(dr/100);
        int ddc=(int)(dc/100);
        abs(ddr)>abs(run_r) ? (ddr=run_r):1;
        abs(ddc)>abs(run_c) ? (ddc=run_c):1;
        envir1.dynamics[i].r=envir1.dynamics[i].dr_start+ddr;
        envir1.dynamics[i].c=envir1.dynamics[i].dc_start+ddc;
        envir1.dynamics[i].h=envir1.get_altitude(envir1.dynamics[i].r,envir1.dynamics[i].c);
        envir1.add_map(envir1.dynamics[i].r,envir1.dynamics[i].c,envir1.dynamics[i].d_altitude);
    }
}
void delete_dynamic_obs(obstacle &envir1){
    for(int i=0;i<envir1.count_dynamic;++i)
        envir1.set_end(envir1.dynamics[i].r,envir1.dynamics[i].c,envir1.dynamics[i].h);
}
void get_level_consu(int action,const Environment &envir1){
    double speed_re;
    if(action==0||action==2||action==-2){
        if(dr[direction])
            speed_re=flight.level_speed-envir1.r_windspeed*dr[direction];
        if(dc[direction])
            speed_re=flight.level_speed-envir1.c_windspeed*dc[direction];
    }
    else{
        if(dr[direction])
            speed_re=flight.level_speed/1.414-envir1.r_windspeed*dr[direction]
                    +flight.level_speed/1.414-envir1.c_windspeed*dr[direction]*action;
        if(dc[direction])
            speed_re=flight.level_speed/1.414-envir1.c_windspeed*dc[direction]
                    +flight.level_speed/1.414-envir1.r_windspeed*dc[direction]*action;
    }
    double power=speed_re/flight.level_speed*flight.level_power;
    energy_consu+=power*get_diatance(action)/flight.level_speed;
}
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
    if(!inside(r,c)||envir1.get_altitude(r,c)>flight.max_altitude){
        r=r_before;
        c=c_before;
        direction=direction_before;
        return -1000;
    }
    double temp=get_later_Qmax();
    get_level_consu(action,envir1);
    if(h>envir1.get_altitude(r,c)&&(r!=r_end||c!=c_end)){
        t=t;
    }
    else if(h>envir1.get_altitude(r,c)&&r==r_end&&c==c_end){
        double dt=(h-envir1.get_altitude(r,c))/flight.vertical_speed;
        h=envir1.get_altitude(r,c);
        energy_consu+=(flight.vertical_speed-envir1.z_windspeed)/flight.level_speed*flight.level_power*dt;
        t+=dt;
    }
    else{
        double dt=(envir1.get_altitude(r,c)-h)/flight.vertical_speed;
        h=envir1.get_altitude(r,c);
        energy_consu+=(flight.vertical_speed+envir1.z_windspeed)/flight.level_speed*flight.level_power*dt;
        t+=dt;
    }
    T+=t;
    t=-t;
    return rate*(gamma*t+temp);
}
void show_result(Environment &envir1){
    for(int i=0;i<n;++i)
    for(int j=0;j<m;++j){
        cout<<i<<j<<endl;
        for(int k=0;k<4;++k){
            for(int o=0;o<5;++o)
            cout<<Q[i][j][k][o]<<" ";
            cout<<endl;
        }
        
    }
    try_init();  
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
        for(int j=0;j<m;++j){
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
    obstacle envir2;
    cout<<"请输入地图数组的尺寸（每一格代表100m*100m）:\n";
    cin>>n>>m;
    cout<<"请输入无人机初始状态：x坐标，y坐标,h高度，以及朝向\n";
    cin>>r_start>>c_start>>h_start>>direction_start;
    cout<<"请上输入无人机目标点位\n";
    cin>>r_end>>c_end>>h_end;
    cout<<"现在请从左到右，从上到下，输入每个地图格的高度\n";
    envir2.get_map();
    envir2.get_obstacle();
    envir2.set_state_map();
    envir2.set_end(r_end,c_end,h_end);
    try_set();
    int episode=0;
    while(episode<50000){
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
            add_dynamic_obs(envir2);
            double reward=move_t(actions[op],envir2);
            Q[r_before][c_before][direction_before][op]=reward+(1-rate)*Q[r_before][c_before][direction_before][op];
            delete_dynamic_obs(envir2);
            if(r==r_end&&c==c_end){
                Q[r_before][c_before][direction_before][op]+=20;
          //      cout<<episode<<" "<<j<<" "<<r_before<<" "<<c_before<<" "<<direction_before<<" "<<actions[op]<<" "<<Q[r_before][c_before][direction_before][op]<<endl;
                break;
            }  
        }
    }
    show_result(envir2);
    cout<<"用时"<<T<<endl;  
    cout<<"消耗能量"<<energy_consu<<endl; 
    cout<<"finish\n";
    return 0;
}