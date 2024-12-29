#include <stdio.h>
#include <stdlib.h>
#include "list.h"
struct student{
    struct list_head conn_list;
    char name[16];
    int age;
    int height;
    int weight;
};
struct list_head	stu_list=LIST_HEAD_INIT(stu_list);

int main(){
    
    int i=0;
    for(i=0;i<5;i++){
        struct student *s=malloc(sizeof(struct student));
        sprintf(s->name,"Num%02d",i);
        s->age=18+i;
        s->height=170+i;
        s->weight=60+i;
        list_add(&s->conn_list,&stu_list);//add to head
        //list_add_tail(s,&stu_list);//add to tail
    }
    struct list_head *pos, *n;

	list_for_each_safe(pos, n, &stu_list) {
		struct student* s= list_entry(pos, struct student, conn_list);
        printf("name:%s age:%d height:%d weight:%d\n",s->name,s->age,s->height,s->weight);
	}
    list_for_each_safe(pos, n, &stu_list) {
		struct student* s= list_entry(pos, struct student, conn_list);
        if(s->age==20)
            list_del(&s->conn_list);
	}
    	list_for_each_safe(pos, n, &stu_list) {
		struct student* s= list_entry(pos, struct student, conn_list);
        printf("name:%s age:%d height:%d weight:%d\n",s->name,s->age,s->height,s->weight);
	}
    return 0;
}