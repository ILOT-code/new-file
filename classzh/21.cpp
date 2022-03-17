#include <iostream>
using namespace std;
typedef struct LNode{
    int data;
    struct LNode *next;
}LNode,*LinkList;
int i=0;

LinkList add(LinkList P1,LinkList P2,LinkList Pbefore=NULL){
    if(P2==NULL&&P1==NULL){
        return Pbefore;
    }
    if(P2==NULL){
      return add(P2,P1,Pbefore);
    }
    if(P1==NULL){
        LinkList P=P2->next;
        P2->next=Pbefore;
        return add(P1,P,P2);
    }
    if(P1->data<=P2->data){
        LinkList P=P1->next;
        P1->next=Pbefore;
        return add(P,P2,P1);
        
    }
    else return add(P2,P1,Pbefore);
}
int main(){
  LinkList Pa,Pa1,Pa2,Pa3,Pa4;
  LinkList Pb,Pb1,Pb2,Pb3;
  Pa=(LinkList)malloc(sizeof(LNode));
  Pa1=(LinkList)malloc(sizeof(LNode));
  Pa2=(LinkList)malloc(sizeof(LNode));
  Pa3=(LinkList)malloc(sizeof(LNode));
  Pa4=(LinkList)malloc(sizeof(LNode));
  Pb=(LinkList)malloc(sizeof(LNode));
  Pb1=(LinkList)malloc(sizeof(LNode));
  Pb2=(LinkList)malloc(sizeof(LNode));
  Pb3=(LinkList)malloc(sizeof(LNode));
  Pa->next=Pa1; Pa1->next=Pa2; Pa2->next=Pa3; Pa3->next=Pa4;Pa4->next=NULL;
  Pb->next=Pb1; Pb1->next=Pb2; Pb2->next=Pb3; Pb3->next=NULL;
  Pa1->data=1;Pa2->data=3;Pa3->data=5;Pa4->data=5;
  Pb1->data=2;Pb2->data=4;Pb3->data=6;
  LinkList t=add(NULL,Pb1);
  while(t!=NULL){
    cout<<t->data;
    t=t->next;
  }
  return 0;
}