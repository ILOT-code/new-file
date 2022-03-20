struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 ListNode* removeNthFromEnd(ListNode* head, int n) {
     int cnt=0,i=0;
     ListNode* PP=new ListNode(0, head);
     ListNode* P=PP;
     while(head){
         head=head->next;
         cnt++;
    }
    while(++i<cnt-n+1){
        P=P->next;
    }
    P->next=P->next->next;
    return PP->next;

 }
    ListNode* removeNthFromEnd(ListNode* head, int n) {
      ListNode* p1=head,*p2=head;
     for(int i=0;i<n;++i){
         p1=p1->next;
     }
     if(!p1) return head->next;
     while(p1->next){
         p1=p1->next;
         p2=p2->next;
     }
     p2->next=p2->next->next;
     return head;
    }