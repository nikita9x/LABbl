#include <stdio.h>
#include <stdlib.h>
typedef struct queue queue;
typedef struct stack stack;
typedef struct derevo derevo;
struct derevo{
    derevo *rebenokleft;
    derevo *rebenokright;
    char s;
};
struct queue{
    char s;
    queue *next;
};

struct stack{
    char s;
    stack *prev;
};

void input_vbIr(queue *sp,int *rez){
    char a;
    scanf_s("%c",&a);
    while((a!='\n')&&(a!=' '))
    {
        if(a=='(')
            *rez=*rez+1;
        else if(a==')')
            *rez=*rez-1;
        queue *p;
        p = malloc(sizeof (queue));
        sp->next=p;
        p->s=a;
        p->next=NULL;
        sp=p;
        scanf_s("%c",&a);
    }
}

void print_vbIr(queue *sp){
    while(sp->next!=NULL){
        printf("%c",sp->s);
        sp=sp->next;
    }
    printf("%c",sp->s);
}



stack* add_stack(stack *sp,char a){
    stack *tmp;
    tmp=malloc(sizeof (stack));
    tmp->prev=sp;
    tmp->s=a;
    return tmp;
    }

stack* remove_stack(stack *sp){
    stack *tmp=sp->prev;
    free(sp);
    return tmp;
}

void print_stack(stack *sp){
    while(sp->prev!=NULL){
        printf("%c",sp->s);
        sp=sp->prev;
    }
}

stack* postrdereva (stack *sta,derevo *der){
    if(sta->s!='?')
    {
        printf("%c",sta->s);
        if(sta->s=='*'||sta->s=='/'||sta->s=='+'||sta->s=='-'||sta->s=='^')
        {
            der->s=sta->s;
            sta=remove_stack(sta);
            derevo *tmpl=malloc(sizeof (derevo));
            derevo *tmpr=malloc(sizeof (derevo));
            der->rebenokleft=tmpl;
            der->rebenokright=tmpr;
            sta=postrdereva(sta,der->rebenokright);
            sta=postrdereva(sta,der->rebenokleft);
        }
        else {
            der->s=sta->s;
            der->rebenokleft=NULL;
            der->rebenokright=NULL;
            sta=remove_stack(sta);
        }
    }
    return sta;
}
void vivoduzla(int count,char x){
    for(int i = 0;i<count;i++)
        printf("  ");
    printf("%c""\n",x);
}

int printder(derevo *x,int glub){
    vivoduzla(glub,x->s);
    if(x->rebenokleft!=NULL)
        printder(x->rebenokleft,glub+1);
    if(x->rebenokright!=NULL){
        printder(x->rebenokright,glub+1);
    }
    return 0;
}

stack* postroyeniye_postfiksa(queue *sp,stack *pos,stack *sta){
    sp=sp->next;
    do {
        if(sp->s=='-'||sp->s=='+')
        {
            if(pos->s=='-'||pos->s=='+'||pos->s=='*'||pos->s=='/'||pos->s=='^')
            {
                sta=add_stack(sta,pos->s);
                pos=remove_stack(pos);
                if(pos->s=='-'||pos->s=='+'||pos->s=='*'||pos->s=='/'||pos->s=='^')
                {
                    sta=add_stack(sta,pos->s);
                    pos=remove_stack(pos);
                    if(pos->s=='-'||pos->s=='+'||pos->s=='*'||pos->s=='/'||pos->s=='^')
                    {
                        sta=add_stack(sta,pos->s);
                        pos=remove_stack(pos);
                    }
                    else {pos=add_stack(pos,sp->s);}
                }
                else {pos=add_stack(pos,sp->s);}
            }
            else pos=add_stack(pos,sp->s);
        }
        else if(sp->s==')'){
            while(pos->s!='('){
                sta=add_stack(sta,pos->s);
                pos=remove_stack(pos);
            }
            pos=remove_stack(pos);
        }
        else if(sp->s=='('){
            pos=add_stack(pos,sp->s);
        }
        else if(sp->s=='^'){
            if(pos->s=='^'){
                sta=add_stack(sta,pos->s);
            }
            else pos=add_stack(pos,sp->s);
        }
        else if(sp->s=='*'||sp->s=='/')
        {
            if(pos->s=='*'||pos->s=='/'||pos->s=='^')
            {
                sta=add_stack(sta,pos->s);
                pos=remove_stack(pos);
                if(pos->s=='*'||pos->s=='/'||pos->s=='^')
                {
                    sta=add_stack(sta,pos->s);
                    pos->s=sp->s;
                }
                else {
                    pos=add_stack(pos,sp->s);
                }
            }
            else pos=add_stack(pos,sp->s);

        }
       else
        {
            sta=add_stack(sta,sp->s);
        }
       sp=sp->next;
    }
    while(sp->next!=NULL);

    if(sp->s=='*'||sp->s=='+'||sp->s=='-'||sp->s=='/'||sp->s=='('){
        pos=add_stack(pos,sp->s);
    }
    else if(sp->s==')'){
        while(pos->s!='('){
            sta=add_stack(sta,pos->s);
            pos=remove_stack(pos);
        }
        pos=remove_stack(pos);
    }
   else
    {
        sta=add_stack(sta,sp->s);
    }
    while(pos->prev!=NULL){
        sta=add_stack(sta,pos->s);
        pos=remove_stack(pos);
    }
    return sta;
}

int main()
{
    printf("vvedite vbIra}|{eniye \n");
    queue *sp;
    stack *stas,*pos;
    derevo *der;int rez=0;
    der=malloc(sizeof (derevo));der->rebenokleft=NULL;der->rebenokright=NULL;
    stas=malloc(sizeof (stack));
    sp = malloc(sizeof (queue));
    pos=malloc(sizeof (stack));
    sp->s='?';
    pos->prev=NULL;
    pos->s='?';
    stas->prev=NULL;
    stas->s='?';
    input_vbIr(sp,&rez);
    if(rez!=0){
        printf("oshibka");
        return 0;
    }
    pos=postroyeniye_postfiksa(sp,pos,stas);
    printf("\n");
    postrdereva(pos,der);
    printf("\n");
    printder(der,0);
    return 0;
}
