//算法6.8　普里姆算法
#include  <iostream>
using  namespace  std;

typedef  char  VerTexType;
typedef  int  ArcType;
#define  MVNum  100
#define  MaxInt  32767                                                //表示极大值，即∞

//辅助数组的定义，用来记录从顶点集U到V-U的权值最小的边
struct {
    VerTexType  adjvex;                                                //最小边在U中的那个顶点
    ArcType  lowcost;                                                //最小边上的权值
} closedge[MVNum];

//-  -  -  -  -图的邻接表存储表示-  -  -  -  -
typedef  char  VerTexType;                                            //假设顶点的数据类型为字符型
typedef  int  ArcType;                                                    //假设边的权值类型为整型
typedef  struct {
    VerTexType  vexs[MVNum];                                        //顶点表
    ArcType  arcs[MVNum][MVNum];                            //邻接矩阵
    int  vexnum, arcnum;                                               //图的当前点数和边数
} AMGraph;

int  LocateVex(AMGraph  G  ,  VerTexType  v) {
    //确定点v在G中的位置
    for (int  i  =  0;  i  <  G.vexnum;  ++i)
        if (G.vexs[i]  ==  v)
            return  i;
    return  -1;
}//LocateVex

void  CreateUDN(AMGraph  &G) {
    //采用邻接矩阵表示法，创建无向网G
    int  i  ,  j  ,  k;
//        cout  <<"请输入总顶点数，总边数，以空格隔开:";
    cin  >>  G.vexnum  >>  G.arcnum;                                                        //输入总顶点数，总边数
//        cout  <<  endl;

//        cout  <<  "输入点的名称，如a"  <<  endl;

    for (i  =  0;  i  <  G.vexnum;  ++i) {
//                cout  <<  "请输入第"  <<  (i+1)  <<  "个点的名称:";
        cin  >>  G.vexs[i];                                                                        //依次输入点的信息
    }
    //cout  <<  endl;
    for (i  =  0;  i  <  G.vexnum;  ++i)                                                       //初始化邻接矩阵，边的权值均置为极大值MaxInt
        for (j  =  0;  j  <  G.vexnum;  ++j)
            G.arcs[i][j]  =  MaxInt;
//        cout  <<  "输入边依附的顶点及权值，如a  b  5"  <<  endl;
    for (k  =  0;  k  <  G.arcnum; ++k) {                                                     //构造邻接矩阵
        VerTexType  v1  ,  v2;
        ArcType  w;
//                cout  <<  "请输入第"  <<  (k  +  1)  <<  "条边依附的顶点及权值:";
        cin  >>  v1  >>  v2  >>  w;                                                                //输入一条边依附的顶点及权值
        i  =  LocateVex(G,  v1);    j  =  LocateVex(G,  v2);                //确定v1和v2在G中的位置，即顶点数组的下标
        G.arcs[i][j]  =  w;                                                                        //边<v1,  v2>的权值置为w
        G.arcs[j][i]  =  G.arcs[i][j];                                                //置<v1,  v2>的对称边<v2,  v1>的权值为w
    }//for
}//CreateUDN

int  Min(AMGraph  G) {
    //返回权值最小的点
    int  i;
    int  index  =  -1;
    int  min  =  MaxInt;
    for (i  =  0  ;  i  <  G.vexnum  ;  ++i) {
        if (min  >  closedge[i].lowcost  &&  closedge[i].lowcost  !=  0) {
            min  =  closedge[i].lowcost;
            index  =  i;
        }
    }//for
    return  index;
}//Min

int  MiniSpanTree_Prim(AMGraph  G,  VerTexType  u) {
    int ans = 0;
    int k = LocateVex(G, u);
    for (int j = 0; j < G.vexnum; ++j)
        if (j != k)  closedge[j].lowcost = G.arcs[k][j];
    closedge[k].lowcost = 0;
    for (int i = 1; i < G.vexnum; ++i) {
        k = Min(G);
        ans += closedge[k].lowcost;
        closedge[k].lowcost = 0;
        for (int j = 0; j < G.vexnum; ++j)
            if (j != k && G.arcs[k][j] < closedge[j].lowcost)
                closedge[j].lowcost = G.arcs[k][j];
    }
    return ans;
}

int  main() {
    //cout  <<  "************算法6.8　普里姆算法**************"  <<  endl  <<  endl;
    AMGraph  G;
    CreateUDN(G);

    //cout  <<  "无向图G创建完成！"  <<  endl;

//        cout  <<  "******利用普里姆算法构造最小生成树结果：******"  <<  endl;

//需要实现的函数
    int  ans  =  MiniSpanTree_Prim(G  ,  'a');
//需要实现的函数


    cout << ans << endl;
    return  0;

}//main