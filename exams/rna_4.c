#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
char a[1000][1000],b[1000][1000];
typedef struct node {
    char ch;
    struct node *next;
} Node;
typedef struct LinkList {
    Node *head, *tail;
} LinkList;

Node *getnode (char a){
    Node *new=malloc(sizeof (Node));
    new->ch=a;
    new->next=NULL;
    return new;
}
void append(Node *newnode,LinkList *ll){
    ll->tail->next=newnode;
    ll->tail=newnode;
}

void Display (LinkList *ll){
    Node *ptr=ll->head->next;
    while (ptr->next!=ll->tail){
        printf("%c",ptr->ch);
        ptr=ptr->next;
    }
    printf("%c",ptr->ch);
}

void change (int i,LinkList *ll){
    Node *ptr=ll->head->next;
    Node *preptr=ll->head;
    while (ptr!=ll->tail){
        Node *ptr1=ptr;
        int flag=true;
        for (int k=0;k<strlen(a[i]);k++){
            if (a[i][k]!=ptr1->ch) {flag=false;break;}
            else {ptr1=ptr1->next;}
        // }
        if (flag==true){
            for(int k=0;k<strlen(b[i]);k++){
                preptr->next=getnode(b[i][k]);
                preptr=preptr->next;
            }
            preptr->next=ptr1;
            return;
        }
        ptr=ptr->next;
        preptr=preptr->next;
    }
}



int main (){
    freopen("rna.txt","r",stdin);
    LinkList ll;char tamp[10000];
    Node x;x.ch=0;x.next=NULL;
    ll.head=&x;ll.tail=&x;
    int ntiao,nci;
    scanf("%s",tamp);
    scanf("%d%d",&ntiao,&nci);
    for (int i=0;i<ntiao;i++){
        scanf("%s%s",a[i],b[i]);
    }
    for (int i=0;i<strlen(tamp);i++){
        append(getnode(tamp[i]),&ll);
    }
    // append(getnode(0),&ll);
    for (int p=1;p<=nci;p++){
    for (int i=0;i<ntiao;i++){
        change (i,&ll);
    }
    }
    Display(&ll);

}