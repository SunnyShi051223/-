#include <cstring>
#include <cmath>

#define MAXSIZE 100

class ElemType{
    //数据类型
public:
    int value;
};

struct  SqList{
    ElemType *elem;
    int length;
};


int InitList(SqList *L){
    L->elem=(new ElemType[MAXSIZE]);
    if(!L->elem) return 0;
    L->length=0;
    return 1;
}

void DestroyList(SqList *L){
    if(L->elem){
        delete L->elem;
    }
}

void ClearList(SqList *L){
    L->length=0;
}

int GetLenth(SqList L){
    return L.length;
}

int IsEmpty(SqList L){
    if(L.length==0) return 1;
    return 0;
}

int GetElem(SqList L,int i,ElemType *e){
    if(i<1||i>L.length) return 0;
    *e=L.elem[i-1];
    return 1;
}

int LocateElem(SqList L,ElemType e){
    for(int i=0;i<L.length;i++){
        if(L.elem[i].value==e.value) return i+1;
    }
    return 0;
}//n+1/2;

int ListInsert(SqList *L,int i,ElemType e){
    if(i<1||i>L->length+1) return 0;
    if(L->length==MAXSIZE) return 0;
    for(int j=L->length;j>=i;j--){
        L->elem[j]=L->elem[j-1];
    }
    L->elem[i-1]=e;
    L->length++;
    return 1;
}//n/2

int ListDelete(SqList *L,int i,ElemType *e){
    if(i<1||i>L->length) return 0;
    for(int j=i;j<L->length;j++){
        L->elem[j-1]=L->elem[j];
    }
    L->length--;
    return 1;
}//n-1/2



int main(){
    SqList L;
}