#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#ifndef _LINUX_LIST_H
#define _LINUX_LIST_H
struct list_head {
	struct list_head *next, *prev;
};
#define offsetof(TYPE, MEMBER)	((size_t)&((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({			\
	(type*)((void *)ptr- offsetof(type,member));})

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next=list;
	list->prev = list;
}

static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next= new;
}
static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

static inline void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void __list_del_entry(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
}

static inline void list_del(struct list_head *entry)
{
	__list_del_entry(entry);
}

static inline int list_is_first(struct list_head *entry,struct list_head *head)
{
	return (entry->prev==head);
}
static inline int list_is_last(struct list_head *entry,struct list_head *head)
{
	return (entry->next==head);
}
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)


#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

#endif


#define log(f, args...) do { printf("%s %d ", __FUNCTION__, __LINE__); printf(f, ##args); printf("\n"); } while (0)
#define USE_EXAMPLE_FILE
#ifdef USE_EXAMPLE_FILE
#include <dirent.h>
#endif
//global define

struct Node{
	char array[500];
	struct list_head conn_list;
};


//global var
struct list_head g_listhead=LIST_HEAD_INIT(g_listhead);
char g_cmd[4096];
int g_total_string_len=0;
int g_total_op_count =0;
int g_array_use_len=0;
int g_op_query_index=0;
int g_op_insert_index=0;
char g_op_insert_string[4096];
char g_string[4096];

struct Node* g_split_node=NULL;

void dumpUnrolledlist(){
	struct list_head* pos,*next;
	list_for_each_safe(pos,next,&g_listhead){
		struct Node* node=list_entry(pos,struct Node,conn_list);
		printf("arr:%s\n",node->array);
	}
}

void initUnrolledlist(char *src){
      int len=sqrt(g_total_string_len);
	  if((len*len)<g_total_string_len)
	  		len+=1;
	  g_array_use_len = len;
	  log("len=%d\n",len);
	  int step=0;
	  while(step<g_total_string_len){
		struct Node* node=(struct Node*)malloc(sizeof(struct Node));
		memset(node,0,sizeof(struct Node));
		strncpy(node->array,&src[step],g_array_use_len);
		list_add_tail(&node->conn_list,&g_listhead);
		step+=g_array_use_len;
	  }
}

void queryUnrolledList(int idx){
	// log("");
	struct list_head* pos,*next;
	idx--;
	int current_pos=0;
	list_for_each_safe(pos,next,&g_listhead){
		struct Node* node=list_entry(pos,struct Node,conn_list);
        if((idx>=current_pos)&&(idx<(current_pos+strlen(node->array)))){
			printf("%c\n",node->array[idx-current_pos]);
		}
		current_pos+=strlen(node->array);
	}
	// log("");
}

void splitUnrolledList(int idx){
	struct list_head* pos,*next;
	int current_pos=0;
	list_for_each_safe(pos,next,&g_listhead){
		//log("idx=%d current_pos=%d\n",idx,current_pos);
		struct Node* node=list_entry(pos,struct Node,conn_list);
        if((idx>=current_pos)&&(idx<(current_pos+strlen(node->array)))){
			//log("%c\n",node->array[idx-current_pos]);
			struct Node* new_node=(struct Node*)malloc(sizeof(struct Node));
			memset(new_node,0,sizeof(struct Node));
			strcpy(new_node->array,&node->array[idx-current_pos]);

			//__list_add(&new_node->conn_list,&node->conn_list,node->conn_list.next);
			__list_add(&new_node->conn_list,&node->conn_list,node->conn_list.next);
			node->array[idx-current_pos]='\0';
			memset(&node->array[idx-current_pos],0,g_array_use_len-(idx-current_pos));
			g_split_node = node;
			break;
		}
		current_pos+=strlen(node->array);
	}
}
void insertUnrolledList(int idx,char *src){
   int left=strlen(src);
  if(g_split_node){
	 int step=g_array_use_len-strlen(g_split_node->array);
	 strncat(g_split_node->array,src,g_array_use_len-strlen(g_split_node->array));
	  while(step<left){
		struct Node* node=(struct Node*)malloc(sizeof(struct Node));
		memset(node,0,sizeof(struct Node));
		//log("step=%d\n",step);
		strncpy(node->array,&src[step],g_array_use_len);
		__list_add(node,&g_split_node->conn_list,g_split_node->conn_list.next);
		g_split_node=node;
		step+=strlen(node->array);
		//log("step=%d\n",step);
	  }
	 
  }
}



void mergeUnrolledList(){
	struct list_head* pos,*next;
	list_for_each_safe(pos,next,&g_listhead){
		struct Node* pos_node=list_entry(pos,struct Node,conn_list);
		struct Node* next_node=list_entry(next,struct Node,conn_list);
		if((strlen(pos_node->array)+strlen(next_node->array))<=g_array_use_len){
				strcat(pos_node->array,next_node->array);
			struct list_head *tmp=next->next;
			list_del(&next_node->conn_list);	
			free(next_node);
			next=tmp;
		}
	}
}
int main() {
#ifdef USE_EXAMPLE_FILE   
     FILE *file;
	 DIR *d;
     struct dirent *dir;
	 char path[1024]={0};
     d = opendir("data");
	if(d){
		 while ((dir = readdir(d)) != NULL) {             
			snprintf(path, sizeof(path), "%s/%s", "data", dir->d_name);
			if(!strcmp(dir->d_name,".")||!strcmp(dir->d_name,".."))
				continue;
			log("######try to open %s ", path); 
#if 0			
            if (dir->d_type != DT_REG) {
                continue;
            }			
#endif		
			file = fopen(path, "r"); 
			if (file == NULL) {
				perror("open file failure");
				continue;
			}else{
				printf(":\n");
			}
#else
	FILE *file=stdin;
#endif
	int line=0;
	char op=0;
    while ((fgets(g_cmd, sizeof(g_cmd), file) != NULL)) {
		 switch(line){
			case 0:
				sscanf(g_cmd,"%d %d",&g_total_string_len,&g_total_op_count);
				//log("g_total_string_len=%d, g_total_op_count=%d",g_total_string_len,g_total_op_count);				
				break;
			case 1:
				sscanf(g_cmd,"%s",&g_string);
				//log("g_string=%s",g_string);	
				initUnrolledlist(g_string);
				//dumpUnrolledlist();
				break;
			default:
				sscanf(g_cmd,"%c",&op);
				//log("op=%c\n",op);
				if(op=='Q'){
					sscanf(g_cmd,"%*s %d",&g_op_query_index);
					//log("g_op_query_index=%d\n",g_op_query_index);
					queryUnrolledList(g_op_query_index);
				}else if(op=='I'){
					sscanf(g_cmd,"%*s %d %s",&g_op_insert_index,g_op_insert_string);
					//log("g_op_insert_index=%d string:%s\n",g_op_query_index,g_op_insert_string);
					log("");
					splitUnrolledList(g_op_insert_index);
					log("");
					dumpUnrolledlist();
					insertUnrolledList(g_op_insert_index,g_op_insert_string);
					log("");
					dumpUnrolledlist();
					mergeUnrolledList();
					log("");
					dumpUnrolledlist();
				}
				break;
		 }
		 line++;
    } 
#ifdef USE_EXAMPLE_FILE    
			fclose(file);
			log("#########try to close %s ", path); 
		}
		closedir(d);
	}
#endif   
    return 0;
}
