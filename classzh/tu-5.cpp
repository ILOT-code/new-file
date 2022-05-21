#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define MAX_VERTEX_NUM 20;
#define InfoType int;
#define VertexType int;
typedef struct ArcNode {
	int adjvex;
	struct ArcNode *nextarc;
	InfoType *info;
} ArcNode;

typedef struct VNode {
	VertexType data;
	ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
	int kind;
} ALGraph;

int main() {
	int numb;
	ALGraph G;
	//求出度
	int d1 = 0;
	ArcNode *p = G.vertices[numb].firstarc;
	while (p != NULL) {
		d1++;
		p = p->nextarc;
	}
	//求入度
	int d2 = 0;
	for (int i = 0; i < vexnum; ++i) {
		if (i == numb) continue;
		ArcNode *p = G.vertices[i].firstarc;
		while (p != NULL) {
			if (p->adjvex == numb) d2++;
			p = p->nextarc;
		}
	}
}
