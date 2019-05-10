#include <stdio.h>
#include <stdlib.h>
void spravka(){
    printf("a - dobavleniye uzla\n"
           "d - udaleniye uzla\n"
           "p - vbIvod dereva\n"
           "i - proverka vse li listya na odnnom urovne\n"
           "h - vivod spravki\n");

}
char scanirovatb()
{
    char a;
    scanf_s("%c",&a);
    while((a==' '||a=='\n'))
        scanf_s("%c",&a);
    return a;
}

typedef struct derevo derevo;
struct derevo
{
    derevo *brat;
    derevo *rebenok;
    char s;
};

void addbrat(derevo *der,char a)
{
    if(der->brat==NULL)
    {
        derevo *p;
        p = malloc(sizeof (derevo));
        der->brat=p;
        p->brat=NULL;
        p->rebenok=NULL;
        p->s=a;
    }
    else addbrat(der->brat,a);
}

void vivoduzla(int count,char x){
    for(int i = 0;i<count;i++)
        printf("  ");
    printf("%c""\n",x);
}


void adduzel(derevo *der,char a)
{
    if(der->rebenok==NULL)
    {
        derevo *p;
        p = malloc(sizeof (derevo));
        der->rebenok=p;
        p->brat=NULL;
        p->rebenok=NULL;
        p->s=a;}
    else {addbrat(der->rebenok,a);}
}

int poiskadd(derevo* der,char to,char a,int *rez){
    if(*rez==1)
        return 1;
    if(der->s==to){
        adduzel(der,a);
        *rez=1;
    }
    else{
        if(der->rebenok!=NULL){
            poiskadd(der->rebenok,to,a,rez);}
        if(der->brat!=NULL){
            poiskadd(der->brat,to,a,rez);}
    }
    return 0;
}

int printder(derevo *x,int glub){
    vivoduzla(glub,x->s);
    if(x->rebenok!=NULL)
        printder(x->rebenok,glub+1);
    if(x->brat!=NULL){
        printder(x->brat,glub);
    }
    return 0;
}

int delluzel(derevo *der,int *rez){
    if(*rez==1)
        return 0;
    if(der->brat!=NULL){
        delluzel(der->brat,rez);
        *rez=1;
        free(der->brat);
    }
    if(der->rebenok!=NULL){
        delluzel(der->rebenok,rez);
        *rez=1;
        free(der->rebenok);
    }
return 0;}


int poiskdel(derevo *der,char to,int *rez){
    if(*rez==1)
        return 1;
    if(der->brat!=NULL){
        if(der->brat->s==to){
            printf("%d",2);
            int d=-1;
            if(der->brat->rebenok!=NULL)
                delluzel(der->brat->rebenok,&d);
            derevo *p=der->brat;
            der->brat=der->brat->brat;
            free(p);
            *rez=1;
        }
    }
    if(der->rebenok!=NULL){
        if(der->rebenok->s==to){
            int d=-1;
            if(der->rebenok->rebenok!=NULL)
                delluzel(der->rebenok->rebenok,&d);
            derevo*p=der->rebenok;
            der->rebenok=der->rebenok->brat;
            free(p);
            *rez=1;
        }
    }
    if(der->rebenok!=NULL){
        poiskdel(der->rebenok,to,rez);}
    if(der->brat!=NULL){
        poiskdel(der->brat,to,rez);}
    return 0;
}

int isthesamelevel(derevo *x,int curlvl,int *wrldlvl){
    if(*wrldlvl==-2){
        return 0;
    }
    if(x->rebenok==NULL){
        if(*wrldlvl==-1)
            *wrldlvl=curlvl;
        else {
            if(*wrldlvl!=curlvl){
               *wrldlvl=-2;
                return 0;
            }
        }
    }
    if(x->rebenok!=NULL){
        isthesamelevel(x->rebenok,curlvl+1,wrldlvl);
    }
    if(x->brat!=NULL){
        isthesamelevel(x->brat,curlvl,wrldlvl);
    }
    return 1;
}
int main(){
    derevo *boss=malloc(sizeof (derevo));
    boss->rebenok=NULL;
    boss->brat=NULL;
    boss->s='a';
    char x;int rez;char a,b;
    spravka();
    while(scanf_s("%c",&x)){
        if(x=='p'){
            printder(boss,0);
        }
        else if(x=='i'){
            rez=-1;
            isthesamelevel(boss,0,&rez);
            if(rez==-2)
                printf("NO \nvvedite sled komandu");
            else
                printf("YES \nvvedite sled komandu");
        }
        else if(x=='a'){
            printf("Vvedite otza i znacheniye uzla \n");
            a=scanirovatb();
            b=scanirovatb();
            rez=-1;
            poiskadd(boss,a,b,&rez);
            if(rez==-1)
                printf("Net otza \nvvedite sled komandu");
            if(rez==1)
                printf("Dobavleno \nvvedite sled komandu");
        }
        else if(x=='d'){
            printf("vvedite udalyaemiy uzel \n");
            a=scanirovatb();rez=-1;
            poiskdel(boss,a,&rez);
            if(rez==-1)
                printf("net uzla \nvvedite sled komandu");
            if(rez==1)
                printf("udaleno \nvvedite sled komandu");
        }
        else if(x=='h'){
            spravka();
        }
        else if(x=='e'){
            printf("programma zakonchila rabotu");
            break;
        }

    }
    return 0;
}
