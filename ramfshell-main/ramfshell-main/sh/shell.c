#include "ramfs.h"
#include "shell.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <libgen.h>
struct list_head shell_path_list;
struct list_head shell_path_list2;
int cmd_return_value=0;
int sls(const char *pathname) {
	print("ls %s\n", pathname);
	cmd_return_value=0;
	node*r=find(pathname);
  	log("errno=%d\n",errno);
	clearAssertbuf();
  	switch(errno){
		  	case EOK:
				//file
				dump2Assertbuf("%s\n",pathname);
				break;
			case EEXIST:
				if(NODE_IS_DIR(r)){					
					struct list_head *p, *n;
					int first=1;
					list_for_each_safe(p, n, &r->offspring_list) {
						node* c= list_entry(p, node,sibling_list );
						dump2Assertbuf("%s%s",(first)?"":" ",NODE_NAME(c));
						first=0;				
					}	
					dump2Assertbuf("\n");
				}else
				   dump2Assertbuf("ls: cannot access '%s': Not a directory\n",pathname);	
				break;
			case ENOFILE:
				dump2Assertbuf("ls: cannot access '%s': No such file or directory\n",pathname);		
				break;
			case EINVAL:				
			default:
				dump2Assertbuf("ls: cannot create directory '%s': Invalid parameter\n",pathname);
				break;
	  }
	if(errno!=EOK){
		cmd_return_value=1;
	}
	return cmd_return_value;

}

int scat(const char *pathname) {
  print("cat %s\n", pathname);
  int fd=ropen(pathname,O_RDONLY);
  clearAssertbuf();
  log("fd=%d errno=%d\n",fd,errno);
  cmd_return_value=0;
  if(fd>=0){
	if(NODE_IS_DIR(fdesc[fd].f)){
		rclose(fd);
		errno=EISDIR;
		goto out;
	}
  	char buf[1024]={0};
	unsigned readcnt=0;
  	while((readcnt=rread(fd,buf,sizeof(buf)))>0){
		int i=0;
		for(i=0;i<readcnt;i++){
			if(isprint(buf[i]))
				dump2Assertbuf("%c", buf[i]);
			else{
				if(buf[i]=='\n')
					dump2Assertbuf("\n");
				else
					dump2Assertbuf(".");	
			}
		}		
  	}
	dump2Assertbuf("\n");	
  	rclose(fd);
  }
 out: 
 log("errno=%d\n",errno);
  {
  	switch(errno){
		  	case EOK:
				break;
			case EISDIR:
				dump2Assertbuf("cat: %s: Is a directory\n",pathname);
				break;
			case ENOTDIR:
				dump2Assertbuf("cat: %s: Not a directory\n",pathname);
				break;
			case ENOFILE:
			case ENOENT:
				dump2Assertbuf("cat: %s: No such file or directory\n",pathname);		
				break;
			case EINVAL:				
			default:
				dump2Assertbuf("cat: cannot create directory '%s': Invalid parameter\n",pathname);
				break;
		  }
  }
  if(errno!=EOK){
		cmd_return_value=1;
	}
	return cmd_return_value;
}

int smkdir(const char *pathname) {
  print("mkdir %s\n", pathname);
  int ret=rmkdir(pathname);
  clearAssertbuf();
  log("ret=%d errno=%d\n",ret,errno);
  cmd_return_value=0;
  if(ret==-1){
		  switch(errno){
		  	case EOK:
				break;
			case ENOENT:
				dump2Assertbuf("mkdir: cannot create directory '%s': No such file or directory\n",pathname);
				break;
			case ENOTDIR:
				dump2Assertbuf("mkdir: cannot create directory '%s': Not a directory\n",pathname);
				break;
			case EEXIST:
				dump2Assertbuf("mkdir: cannot create directory '%s': File exists\n",pathname);		
				break;
			case ENAMETOOLONG:
				dump2Assertbuf("mkdir: cannot create directory '%s': name too long\n",pathname);
				break;
			case EINVAL:				
			default:
				dump2Assertbuf("mkdir: cannot create directory '%s': Invalid parameter\n",pathname);
				break;
		  }
  }
  if(errno!=EOK){
		cmd_return_value=1;
	}
	return cmd_return_value;
}

int stouch(const char *pathname) {
  print("touch %s\n", pathname);
  clearAssertbuf();
  cmd_return_value=0;
  int fd=ropen(pathname,O_CREAT);  
  switch(errno){
		  	case EOK:
				break;
			case ENOENT:
				dump2Assertbuf("touch: cannot touch '%s': No such file or directory\n",pathname);
				break;
			case ENOTDIR:
				dump2Assertbuf("touch: cannot touch '%s': Not a directory\n",pathname);
				break;
			case EEXIST:	
				break;
			case ENAMETOOLONG:
				dump2Assertbuf("touch: cannot touch '%s': name too long\n",pathname);
				break;
			case EINVAL:				
			default:
				dump2Assertbuf("touch: cannot touch '%s': Invalid parameter\n",pathname);
				break;
		  }
	if(fd>=0)
  		rclose(fd);
 if(errno!=EOK){
		cmd_return_value=1;
	}
	return cmd_return_value;
}

int secho(const char *content) {
  print("echo %s\n", content);
  char *src=calloc(1,strlen(content)+1);
  strcpy(src,content);
  char *p=trim(src);
  clearAssertbuf();
  while(*p){
	  if(*p=='$'){
		  if(*(p+1)=='?'){
			  dump2Assertbuf("%d",cmd_return_value);
			  p=p+2;//$?
			  continue;	  
		  }else  if(!strncmp(p+1,"PATH",strlen("PATH"))){
			  if((*(p+5)=='\0')||(*(p+5)==' ')){
				  struct list_head *m=NULL, *n=NULL;
				  int first=1;
				  list_for_each_safe(m, n, &shell_path_list) {
					SHELL_PATH* s= list_entry(m, SHELL_PATH,conn_list );
					dump2Assertbuf("%s%s",first?"":":",s->path);
					first=0;
				  }
				  p=p+5;
				  continue;	
			  }else{
				  //$PATHXXX
				  p=p+5;
				  while((*p!=' ')&&(*p!='\0')&&(*p!='\\')){
					  p++;
				  }
				  continue;
			  }				  
		  }
		}else if(*p=='\\'){
			// \*->*
			  if(*(p+1)){
				  dump2Assertbuf("%c",*(p+1));
				  p=p+2;//$?
				  continue;	
			  }		
				p++;
				continue;
		}
	  dump2Assertbuf("%c",*p);
	  p++;
  }

end:
  cmd_return_value=0;
  dump2Assertbuf("\n");	
  if(src)
	  free(src);
  return 0;
}

int swhich(const char *cmd) {
  print("which %s\n", cmd);
  clearAssertbuf();
  cmd_return_value=1;
  struct list_head *p=NULL, *n=NULL;
	list_for_each_safe(p, n, &shell_path_list) {
		SHELL_PATH* s= list_entry(p, SHELL_PATH,conn_list );
		char *buf=calloc(1,strlen(cmd)+strlen(s->path)+10);
		sprintf(buf,"%s/%s",s->path,cmd);
		if(find(buf)){
			dump2Assertbuf("%s",buf);
			cmd_return_value=0;
			break;
		}	
	}
	dump2Assertbuf("\n");	
	return cmd_return_value;
}
void dump_shell(struct list_head* head){
	struct list_head *p=NULL, *n=NULL;
	int first=1;
	list_for_each_safe(p, n, head) {
		SHELL_PATH* s= list_entry(p, SHELL_PATH,conn_list );
		printf("%s%s",first?"":":",s->path);
		first=0;
	}
	printf("\n");
}
void _close_shell(struct list_head* head){
	struct list_head *p=NULL, *n=NULL;
	list_for_each_safe(p, n, head) {
		SHELL_PATH* s= list_entry(p, SHELL_PATH,conn_list );
		list_del(&s->conn_list);
		free(s->path);
		free(s);
	}
}

void process_line(char* line){
	log("line=%s\n",line);	
	line=trim(line);
	if(!strncmp(line,"export",strlen("export"))){
		
		line+=strlen("export");
		line=trim(line);
		//A=B
		char* string_a=line;
		char* string_b=NULL;
		while(line++){
           if(*line=='='){
				*line='\0';
				string_b=(line+1);
		   		break;
           	}		   
		}
		if(!string_a||!string_b)
			return;
		string_a=trim(string_a);
		string_b=trim(string_b);
		log("string_a=%s\n",string_a);
		log("string_b=%s\n",string_b);	
		if(!strlen(string_a)||!strlen(string_a))
			return;
		if(strcmp(string_a,"PATH"))
			return;
		//process A:B:C
		char *tok=strtok(string_b, ":");	
		while (tok!=NULL) {
			log("token=%s\n",tok);
			if(!strcmp(tok,"$PATH")){
				struct list_head *p=NULL, *n=NULL;				
				list_for_each_safe(p, n, &shell_path_list) {
					SHELL_PATH* s= list_entry(p, SHELL_PATH,conn_list );
					list_del(&s->conn_list);
					list_add_tail(&s->conn_list,&shell_path_list2);
				}
			}else{
				SHELL_PATH* new= (SHELL_PATH*)calloc(1,sizeof(SHELL_PATH));
				if(new){
					new->path=(char*)calloc(1,strlen(tok)+1);
					strcpy(new->path,tok);
					list_add_tail(&new->conn_list,&shell_path_list2);
				}
			}
			tok = strtok(NULL, ":");			
		}
		_close_shell(&shell_path_list);
		//shell_path_list2-->shell_path_list
		do{
			struct list_head *p=NULL, *n=NULL;
			list_for_each_safe(p, n, &shell_path_list2) {
				SHELL_PATH* s= list_entry(p, SHELL_PATH,conn_list );
				list_del(&s->conn_list);
				list_add_tail(&s->conn_list,&shell_path_list);
			}
		}while(0);		
		INIT_LIST_HEAD(&shell_path_list2);
	}
}
void init_shell() {
	INIT_LIST_HEAD(&shell_path_list);
	INIT_LIST_HEAD(&shell_path_list2);	
	int fd=ropen("/home/ubuntu/.bashrc",O_RDONLY);
	if(fd>=0){
		char buf[4096]={0};
		int readcnt=0;				
		while(rread(fd,&buf[readcnt],1)){
			if(buf[readcnt]=='\n'){				
				process_line(buf);
				memset(buf,0,readcnt);
				readcnt=0;
			}else	
				readcnt++;
		}
		//last line without \n
		if(strlen(buf)){
			process_line(buf);
			memset(buf,0,readcnt);
			readcnt=0;
		}			
	}
	//dump_shell(&shell_path_list);
}

void close_shell() {
	_close_shell(&shell_path_list);
	_close_shell(&shell_path_list2);
}