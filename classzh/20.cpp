Status InsertX_B(SqList &L, int x){
    if(L.length>=L.listsize){          //如果当前空间已满，增加空间分配；
        int *newbase=(int *)realloc(L.elem,
                        (L.listsize+LISTINCREMENT)*sizeof(int));
        if(!newbase) exit(OVERFLOW);   //如果分配失败，以“溢出”结束程序；
        L.elem=newbase;                //这是新的基地址；
        Listsize+=LISTINCREMENT;       //更新容量；
    } 
    if(x>*(L.elem+L.length-1)){        //如果x比线性表中最大值还大；
        *(L.elem+L.length)=x;
        return OK;
    }
    int i=0;                          //定义的i是x将插入的位置；
    for(;i<L.length;++i)              //找到i的值；
        if(*(L.elem+i)>=x)
            break;
    for(int j=L.length-1;j>=i;--j)    //把L.elem[i]本身以及之后的值全部右移；
        L.elem[j+1]=L.elem[j];
    L.elem[i]=x;                      //把x赋给L.elem[i];
    ++L.length;                       //更新线性表当前长度；
    return ok;
}