#include <cstddef>
#include <cstdio>

typedef int ElemType;

typedef struct Lnode{
    ElemType data;
    struct Lnode *next;
}Lnode,*Linklist;

int InitList(Lnode *L){
    L=new Lnode;
    L->next=NULL;
    return 0;
}

int DestroyList(Lnode *L){
    Linklist p;
    while(L){
        p=L;
        L=L->next;
        delete p;
    }
    return 0;
}

int ClearList(Lnode *L){
    Linklist p,q;
    p=L->next;
    while(p){
        q=p->next;
        delete p;
        p=q;
    }
    L->next=NULL;
    return 0;
}

int GetLenth(Lnode *L){
    int len=0;
    Linklist p;
    p=L->next;
    while(p){
        len++;
        p=p->next;
    }
    return len;
}

int ListEmpty(Lnode *L){
    if(L->next==NULL)
        return 1;
    else
        return 0;
}

int GetElem(Lnode *L,int i,ElemType *e){
    Linklist p;
    p=L->next;
    int j=1;
    while(p&&j<i){
        p=p->next;
    }
    if(!p||j>1){
        return 0;
    }
    *e=p->data;
    return 1;
}

Lnode  *LocateElem(Lnode *L,ElemType e){
    Linklist p;
    p=L->next;
    while(p&&p->data!=e){
        p=p->next;
    }
    return p;
}

int LocateElem(Lnode *L,int i,ElemType *e){
    Linklist p;
    p=L->next;
    int j=1;
    while(p&&j<i){
        p=p->next;
        j++;
    }
    if(p){
        return j;
    }
    return 0;
}

int ListInsert(Lnode *L,int i,ElemType e){
    Linklist p,s;
    p=L;
    int j=0;
    if(!p||j>i-1){
        return 0;
    }
    s=new Lnode;
    s->data=e;
    s->next=p->next;
    p->next=s;
    return 1;
}

int ListDelete(Linklist &L,int i,ElemType &e){
    Linklist p,q;
    p=L;
    int j=0;
    while(p&&j<i-1){
        p=p->next;
    }
    if(!p||p->next==NULL){
        return 0;
    }
    q=p->next;
    p->next=q->next;
    e=q->data;
    delete q;
    return 1;
}

void CreateList(Linklist &L,int n){
    L=new Lnode;
    L->next=NULL;
    for(int i=n;i>0;i++){
        Linklist p=new Lnode;
        scanf("%d",&p->data);
        p->next=L->next;
        L->next=p;
    }
}

void CreateListR(Linklist &L,int n){
    L=new Lnode;
    L->next=NULL;
    Linklist r;
    r=L;
    for(int i=0;i<n;i++){
        Linklist p=new Lnode;
        scanf("%d",&p->data);
        p->next=NULL;
        r->next=p;
        r=p;
    }
}





































int main(){

}