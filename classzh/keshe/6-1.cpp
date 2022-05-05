#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <assert.h>
#include  <stddef.h>
#define  TRUE  1
#define  FALSE  0
#define  OK  1
#define  ERROR  0
#define  INFEASIBLE  -1
#define  OVERFLOW  -2
#define  LIST_INIT_SIZE  100
#define  STACK_INIT_SIZE  100
typedef  int  Status;


#define  MAX_VERTEX_NUM  20
typedef  enum  {DG, DN, AG, AN}  GraphKind; //有向图、有向网、无向图、无向网
typedef  struct  ArcNode {
    int        adjvex;                                        //该弧头的位置
    struct  ArcNode  *nextarc;        //下一条出弧（弧尾相同的下一条弧）
    int                info;                                //附加信息
} ArcNode;       //弧结点

typedef  char  VertexType  ;
typedef  struct  VNode {
    VertexType  data;                        //顶点信息
    ArcNode  *firstarc;        //第一条出弧
} VNode,  AdjList[MAX_VERTEX_NUM];       //邻接表头指针向量

typedef  struct  {
    AdjList  vertices;                //邻接表头指针向量
    int  vexnum, arcnum;               //顶点数目和弧的数目
    GraphKind  kind;                        //图的种类
} ALGraph;

//返回顶点u在图中的位置,未找到返回-1
int  LocateVex(ALGraph  G, VertexType  u)
{   int  i;
    for (i  =  0;  i  <  G.vexnum;  i++)
        if (G.vertices[i].data  ==  u)  return  i;
    return  -1;
}

//创建无向图
void  CreateAG(ALGraph  &G)
{   int  i, j, k, info  =  0;
    VertexType  v1, v2;
    ArcNode  *  p;

//        printf("\n下面分步输入创建无向图的信息：");  G.kind  =  AG;
//        printf("\n1.请输入图的顶点个数：");
    scanf("%d",  &G.vexnum);
//            printf("\n2.请输入图的边的个数：");
    scanf("%d",  &G.arcnum);
//        printf("\n3.请连续输入%d个顶点（字符型）：",G.vexnum);
    scanf("%c", &G.vertices[0].data);       //滤掉换行字符
//        printf("n=%d  e=%d",G.vexnum,G.arcnum);
    for (k  =  0;  k  <  G.vexnum;  k++)       //邻接表头指针向量初始化
    {   scanf("%c",  &G.vertices[k].data);
        G.vertices[k].firstarc  =  NULL;
    }

//                for(k  =  0;  k  <  G.vexnum;  k++)        //邻接表头指针向量初始化
//                printf("%d=%c  "  ,  k,G.vertices[k].data);

    for (k  =  0;  k  <  G.arcnum;  k++)               //建立弧结点<v,w>
    {   //printf("\n建立弧%d,请输入弧的信息,格式为v,w：",k+1);
        scanf("%c", &v1);       //滤掉换行字符
        scanf("%c  %c",  &v1,  &v2);
        i  =  LocateVex(G, v1);  j  =  LocateVex(G, v2);      //确定v1,v2在图中的位置
        if (i  ==  -1  ||  j  ==  -1)
        {  printf("\n输入弧信息非法，程序退出！%c  %c  %d  %d    ", v1,  v2, i, j);  break;  }

        p  =  (ArcNode  *)  malloc(  sizeof(ArcNode)  );
        p->adjvex  =  j;
        p->info  =  info;
        p->nextarc  =  G.vertices[i].firstarc;
        G.vertices[i].firstarc  =  p;

        p  =  (ArcNode  *)  malloc(  sizeof(ArcNode)  );
        p->adjvex  =  i;
        p->info  =  info;
        p->nextarc  =  G.vertices[j].firstarc;
        G.vertices[j].firstarc  =  p;
    }
}

//按邻接表的形式输出无向图
void  PrintAG(ALGraph  G)
{   ArcNode  *p;
    printf("\n无向图G的邻接表形式：");
    for (int  i  =  0;  i  <  G.vexnum;  i++)
    {   printf("\n  %c", G.vertices[i].data);
        if (  G.vertices[i].firstarc  )
        {   printf("-->");
            for (p  =  G.vertices[i].firstarc;  p;  p  =  p->nextarc)
            {   printf("%c", G.vertices[p->adjvex].data);
                if (p->nextarc)  printf("-->");
            }
        }
    }
    printf("\n");
}

//返回v（顶点位置）的第一个邻接顶点的位置，若无返回-1
int  FirstAdjVex(ALGraph  G,  int  v)
{   ArcNode  *p;
    p  =  G.vertices[v].firstarc;
    if (p)  return  p->adjvex;
    else  return  -1;
}

//返回v相对于w（顶点位置）的下一个邻接顶点的位置，若无返回-1
int  NextAdjVex(ALGraph  G,  int  v,  int  w)
{   ArcNode  *p;
    for (p  =  G.vertices[v].firstarc;  p->nextarc;  p  =  p->nextarc)
        if (p->adjvex  ==  w)  return  p->nextarc->adjvex;

    return  -1;
}
//level表明当前递归调用的层次，也即v,j的路径长度
//此算法遍历全部v->j的路径，直到找到长度为k的为止
VertexType  Path[MAX_VERTEX_NUM];
int  p;
int  visited[MAX_VERTEX_NUM];

void  DFS(ALGraph  G, int  v, int  j, int  k, int  level) {
    if(level > k+1) return;
    Path[level] = G.vertices[v].data;
    if (v == j && level == k + 1) {
        for (int i = 1; i <= level; ++i) printf("%c ", Path[i]);
        printf("\n");
    }
    int u = FirstAdjVex(G, v);
    for (; u != -1; u = NextAdjVex(G, v, u)) {
        DFS(G, u, j, k, level + 1);
    }

}

//判断vi->vj是否有长度为k的简单路径

void  PathDFS(ALGraph  G, VertexType  vi, VertexType  vj, int  k)
{   int  i, j;
    for (i  =  0;  i  <  G.vexnum;  i++)  visited[i]  =  0;       //初始化顶点访问标志
    p  =  0;
    i  =  LocateVex(G, vi);  j  =  LocateVex(G, vj);      //确定vi,vj在图中的位置
    if (i  ==  -1  ||  j  ==  -1)
    {  printf("\n输入顶点信息非法，程序退出！");  return  ;  }

    Path[p++]  =  G.vertices[i].data;
    DFS(G, i, j, k, 1);    //从i出发深度优先搜索
}

int  main()
{
    int  k;
    VertexType  vi, vj;

    ALGraph  G;
    CreateAG(G);
    //  PrintAG(G);

    //printf("\n判断是否存在由vi到vj的长度为k的简单路径,请输入vi、vj和k：");
    scanf("%c", &vi);
    scanf("%c  %c  %d", &vi, &vj, &k);
    PathDFS(G, vi, vj, k);
    printf("\n");
    return  OK;
}