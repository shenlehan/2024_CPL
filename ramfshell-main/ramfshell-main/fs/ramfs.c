#include "ramfs.h"
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <libgen.h>


node *root = NULL;
int errno=0;

FD fdesc[NRFD];
char assertbuf[4096]={0};
int assert_mode=0;
void enable_assert(){
	assert_mode=1;
}
void disable_assert(){
	assert_mode=0;
}

void clearAssertbuf(){
	memset(assertbuf,0,sizeof(assertbuf));
}
void dump2Assertbuf(char *format, ... ){
	if(assert_mode==1){
		va_list args;	
		va_start(args, format);	
		vsnprintf(&assertbuf[strlen(assertbuf)], sizeof(assertbuf)-strlen(assertbuf), format, args);	
		va_end(args);
	}else{
		va_list args;	
		va_start(args, format);	
		vprintf(format, args);	
		va_end(args);
	}
}
void printAssertbuf(){
//	if(assert_mode==0)
//		printf("%s",assertbuf);
}

void dump_buffer(const unsigned char *inBuff, int inSize, char *type, char *seps) {
    int i;
    for (i = 0; i < inSize; i++) {
        unsigned char c = inBuff[i];
        if (i != 0) dump("%s", seps == NULL ? "" : seps);

        if (type != NULL && strcmp(type, "C") == 0) {
            dump("%c", isprint(c) ? c : '.');  // 以字符形式打印
        } else if (type != NULL && strcmp(type, "H") == 0) {
            dump("%02x", c);                   // 以十六进制形式打印
        } else {
            dump("%02x/%c", c, isprint(c) ? c : '.');  // 以十六进制和字符形式打印
        }
    }
}
int updateFdFlags(int flags){
	/*
	O_CREAT：仅创建
	O_RDONLY: 仅可读
	O_WRONLY: 仅可写
	O_RDWR：可读写
	O_CREAT | O_RDWR：创建与读写
	O_CREAT | O_RDONLY：创建与只读
	O_CREAT | O_WRONLY：创建与只写  
	O_CREAT | O_RDWR | O_WRONLY：创建与只写（见前文说明）
	O_APPEND | O_RDWR：追加可读写（追加时只需要在open时设置offset即可，之后的write不需要再设置offset，可以参考样例4）
	O_APPEND | O_WRONLY：追加与只写
	O_TRUNC | O_WRONLY | O_RDWR：覆盖与只写（见前文说明）
	*/
	if(flags==(O_CREAT | O_RDWR | O_WRONLY)){
		flags=O_CREAT|O_WRONLY;
	}
	if(flags==(O_TRUNC | O_WRONLY | O_RDWR)){
		flags=O_TRUNC|O_WRONLY;
	}
	return flags;
}
char *trim(char *str)
{
    char *end;

    while (isspace((unsigned char)*str))
    {
        str++;
    }

     if (*str == 0)
    {
        return str;
    }

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
    {
        end--;
    }

    end[1] = '\0';

    return str;
}

/*
	errno=ENOFILE;  //1:/home[Y]/ubuntu[Y]/data.txt[N] 2:/home[Y]/ubuntu[N]/
	errno=ENOENT;   //1:/home[Y]/ubuntu[N]/data.txt
	errno=EEXIST;   //1:/home[Y]/data.txt[Y] 2:/home[Y]/ubuntu[Y]
	errno=ENOTDIR;  //1:/home[Y]/data.txt/123.txt
*/

int ropen(const char *pathname, int flags) {
	int ret=-1;
	errno=EOK;
	node* parent=NULL;
	node* cur=NULL;
	flags=updateFdFlags(flags);
	log("pathname=%s\n",pathname);
	char basename[MAX_NAME_LEN]={0};
	cur=_find(pathname,&parent,basename);
	log("####### is errno=%d \n",errno);
	if(errno==ENOFILE){
		if(flags&O_CREAT){
			//not exist file,create it
			//but can't create dir
			if(pathname[strlen(pathname)-1]=='/'){
				//touch /home/ubuntu/test/
				errno==ENOFILE;
				ret=-1;
			}else{
				log("parent is %s name %s \n",NODE_NAME(parent),basename);
				node* new=addNode(parent,basename,FNODE);
				if(new){
					int new_fd=fetch_fd(0,flags,new);
					if(new_fd!=-1){																		
						errno=EOK;						
					}
					ret=new_fd;
				}
			}
		}
	}else if(errno==EEXIST){
		if(NODE_IS_DIR(cur)){
			errno=EISDIR;
			//ret=-1; 
			log("open a dirctory");
			int new_fd=fetch_fd(0,flags,cur);
			if(new_fd!=-1){
				ret=new_fd;
			}
			goto end;
		}
		int new_fd=fetch_fd(0,flags,cur);
		if(new_fd!=-1){							
			errno=EOK;
			ret=new_fd;		
			if(flags&O_APPEND){
				fdesc[new_fd].offset=cur->size;
			}
			if(flags&O_TRUNC){
				free_file_content(cur);
				fdesc[new_fd].offset=0;
			}
		}
		
	}else{
		ret=-1;
	}	
end:	
	log("fopen return fd %d \n",ret);
	return ret;
}
void init_fd(){
	memset(fdesc,0,sizeof(FD)*NRFD);
}
int fetch_fd(int offset,int flags,node* n){
	int i=0;
	for(i=0;i<NRFD;i++){
		if(fdesc[i].used)
			continue;
		fdesc[i].used=true;
		fdesc[i].offset=offset;
		fdesc[i].flags=flags;
		fdesc[i].f=n;
		break;
	}
	if(i==NRFD){
		errno=ENFILE;
		log("No valid fd,has max\n");
		return -1;
	}
	return i;
}

int rclose(int fd) {
	if((fd>=0&&fd<NRFD)){
		if(fdesc[fd].used){
			fdesc[fd].used=false;
			fdesc[fd].offset=0;
			fdesc[fd].flags=0;
			fdesc[fd].f=NULL;
			log("close fd %d successfully\n",fd);
			return 0;
		}else
			return -1;
	}else{
		print("[Error] invalud fd %d\n",fd);
		return -1;
	}
}
int show_fd(){
	int i=0;
	printf("Currrent using fd:\n");
	for(i=0;i<NRFD;i++){
		if(fdesc[i].used){
			printf("\t name=%s\n",NODE_NAME(fdesc[i].f));
			
		}		
	}
}
ssize_t rwrite(int fd, const void *buf, size_t count) {
	log("\n");
	errno=EOK;
	unsigned int total_space=0;
	unsigned int left_space=0;
	unsigned int has_write=0;
	if((fd>=0&&fd<NRFD)){
		if(fdesc[fd].used==false){
			errno=EBADF;
			return -1;
		}
		if(!(fdesc[fd].flags&(O_WRONLY|O_RDWR|O_APPEND ))){
			errno=EBADF;
			return -1;
		}
		if(NODE_IS_DIR(fdesc[fd].f)){
			errno=EISDIR;
			return -1;
		}

		//write buf
		//step 1:get left space room
		struct list_head *p, *n;
		log("count=%d\n",count);

		if(list_empty(&(fdesc[fd].f->content_list))){
			struct CONTENT* c=calloc(1,sizeof(struct CONTENT));
			list_add_tail(&c->con_list,&(fdesc[fd].f->content_list));
		}
		list_for_each_safe(p, n, &(fdesc[fd].f->content_list)) {
			struct CONTENT* c= list_entry(p, struct CONTENT, con_list);
			if((fdesc[fd].offset>=total_space)&&(fdesc[fd].offset<(total_space+EACH_CONTENT_LEN))){
				int left_space_on_this_content=total_space+EACH_CONTENT_LEN-fdesc[fd].offset;
				log("total_space=%d left_space_on_this_content=%d fdesc[fd].offset=%d\n",total_space,left_space_on_this_content,fdesc[fd].offset);
				if(left_space_on_this_content>=count){
					log("write count=%d\n",count);
					memcpy(&c->content[fdesc[fd].offset-total_space],buf+has_write,count);
					if(c->using<=(fdesc[fd].offset-total_space+count))
						c->using=fdesc[fd].offset-total_space+count;
					fdesc[fd].offset+=count;
					has_write+=count;
					count-=count;
					log("has_write=%d\n",has_write);
					break;
				}else{
					memcpy(&c->content[fdesc[fd].offset-total_space],buf+has_write,left_space_on_this_content);
					c->using=EACH_CONTENT_LEN;
					fdesc[fd].offset+=left_space_on_this_content;
					count-=left_space_on_this_content;
					has_write+=left_space_on_this_content;
					log("has_write=%d\n",has_write);
					//new alloc page
					total_space+=EACH_CONTENT_LEN;
					if(list_is_last(&c->con_list,&(fdesc[fd].f->content_list))){
						struct CONTENT* c=calloc(1,sizeof(struct CONTENT));
						list_add_tail(&c->con_list,&(fdesc[fd].f->content_list));
						log("new alloc page\n",count);
						n=&c->con_list;//update n node
					}
					
				}
			}else{
				total_space+=EACH_CONTENT_LEN;
				c->using=EACH_CONTENT_LEN;
				if(list_is_last(&c->con_list,&(fdesc[fd].f->content_list))){
					struct CONTENT* c=calloc(1,sizeof(struct CONTENT));
					list_add_tail(&c->con_list,&(fdesc[fd].f->content_list));
					n=&c->con_list;//update n node
					log("new alloc page\n",count);
				}
			}
	       	        
		}
		if(fdesc[fd].f->size<=(fdesc[fd].offset))
			fdesc[fd].f->size=fdesc[fd].offset;
			
#if 0		
		while(total_space<fdesc[fd].offset){
			//malloc new CONTENT
			struct CONTENT* c=calloc(1,sizeof(struct CONTENT));
			list_add_tail(&c->con_list,&(fdesc[fd].f->content_list));
			total_space+=EACH_CONTENT_LEN;
		}

		left_space=total_space-fdesc[fd].offset;
		
		xlog2("File %s size %u total_space:%u left:%u\n",NODE_NAME(fdesc[fd].f),fdesc[fd].f->size,total_space,total_space-fdesc[fd].f->size);
		if(left_space&&(left_space>=count)){
			struct CONTENT* c=list_last_entry(&fdesc[fd].f->content_list,struct CONTENT,con_list);
			memcpy(c->content+c->using,buf,count);
			c->using+=count;
			fdesc[fd].f->size+=count;
		}else{
			//total left spacet not enough
			//firstly use up
			if(left_space){
				struct CONTENT* c=list_last_entry(&fdesc[fd].f->content_list,struct CONTENT,con_list);
				memcpy(c->content+c->using,buf+has_write,left_space);
				c->using+=left_space;
				fdesc[fd].f->size+=left_space;
				has_write+=left_space;
			}
			count-=left_space;
			//malloc new CONTENT
			while(count){
				struct CONTENT* c=calloc(1,sizeof(struct CONTENT));
				list_add_tail(&c->con_list,&(fdesc[fd].f->content_list));
				if(count<=EACH_CONTENT_LEN){
					memcpy(c->content,buf+has_write,count);
					c->using=count;
					fdesc[fd].f->size+=count;
					has_write+=count;
					count=0;
				}else{
					memcpy(c->content,buf+has_write,EACH_CONTENT_LEN);
					c->using=EACH_CONTENT_LEN;
					fdesc[fd].f->size+=EACH_CONTENT_LEN;
					has_write+=EACH_CONTENT_LEN;
					count-=EACH_CONTENT_LEN;
				}
			}
			
		}
#endif		
		log("File %s size %u has_write:%d\n",NODE_NAME(fdesc[fd].f),fdesc[fd].f->size,has_write);
		return  has_write;
	}else{
		errno=EBADF;
		return -1;
	}
}

ssize_t rread(int fd, void *buf, size_t count) {
	errno=EOK;
	log("\n");
	if((fd>=0&&fd<NRFD)){
		if(fdesc[fd].used==false){
			errno=EBADF;
			return -1;
		}
		log("fdesc[fd].flags=%d\n",fdesc[fd].flags);
		if(!(fdesc[fd].flags&(O_RDWR|O_RDONLY ))){
			errno=EBADF;
			return -1;
		}
		if(NODE_IS_DIR(fdesc[fd].f)){
			errno=EISDIR;
			xlog("\n");
			return -1;
		}
		log("\n");
		struct list_head *p, *n;
		
		unsigned int readcnt=0;
		unsigned int offset=0;
		list_for_each_safe(p, n, &(fdesc[fd].f->content_list)) {
			struct CONTENT* c= list_entry(p, struct CONTENT, con_list);
			log("offset=%d fd_offset=%d using=%d readcnt=%d\n",offset,fdesc[fd].offset,c->using,readcnt);
			if((offset+c->using)<fdesc[fd].offset){
				offset+=c->using;
				continue;
			}else{
				unsigned int left=c->using+offset-fdesc[fd].offset;
				log("offset=%d fd_offset=%d using=%d count=%d readcnt=%d left=%d\n",offset,fdesc[fd].offset,c->using,count,readcnt,left);
				if(left>=count){
					memcpy(buf+readcnt,c->content+fdesc[fd].offset-offset,count);					
					fdesc[fd].offset+=count;
					offset+=count;
					readcnt+=count;
					count-=count;
#if 0					
					int i=0;
					char *str=(char*)buf;
					for(i=0;i<readcnt;i++){
						printf("%c",str[i]);
					}
					printf("\n");
#endif					
					log("offset=%d fd_offset=%d using=%d count=%d readcnt=%d\n",offset,fdesc[fd].offset,c->using,count,readcnt);
					break;
				}else{
					memcpy(buf+readcnt,c->content+fdesc[fd].offset-offset,left);
					fdesc[fd].offset+=left;
					//offset+=left;
					offset+=c->using;
					readcnt+=left;
					count-=left;
					log("offset=%d fd_offset=%d using=%d count=%d readcnt=%d\n",offset,fdesc[fd].offset,c->using,count,readcnt);
				}
			}        
		}
		return readcnt;
	}else{
		errno=EBADF;
		return -1;
	}
}

off_t rseek(int fd, off_t offset, int whence) {
	errno=EOK;
	if((fd>=0&&fd<NRFD)){
		if(fdesc[fd].used==false){
			errno=EBADF;
			return -1;
		}
		switch(whence){
			case SEEK_SET:
				if(offset<0){
					errno=EINVAL;
					return -1;
				}				
				fdesc[fd].offset=offset;					
				break;
			case SEEK_CUR:
				if((fdesc[fd].offset+offset)<0){
					errno=EINVAL;
					return -1;
				}
				fdesc[fd].offset+=offset;
				break;
			case SEEK_END:
				if((fdesc[fd].f->size+offset)<0){
					errno=EINVAL;
					return -1;
				}
				fdesc[fd].offset=fdesc[fd].f->size+offset;
				break;
		}
		log("fdesc[%d].offset=%d fdesc[fd].f->size=%d\n",fd,fdesc[fd].offset,fdesc[fd].f->size);
		return fdesc[fd].offset;
	}
	errno=EBADF;
	return -1;
}
node *findNode(node*s,char* name){
	log("try to find %s in %s\n",name,NODE_NAME(s));
	struct list_head *p=NULL, *n=NULL;
	node* ret=NULL;
	list_for_each_safe(p, n, &s->offspring_list) {
		node* c= list_entry(p, node,sibling_list );
		if(!strcmp(NODE_NAME(c),name)){
			log("Find out %s in %s\n",name,NODE_NAME(s));
			ret=c;
			break;
		}
	}
	return ret;
}
node* addNode(node* s,char* name,int type){
	node *new=(node *)calloc(1,sizeof(node));
	if(new){
		new->name=calloc(1,strlen(name)+1);
		strcpy(new->name,name);
		new->size=0;
		new->type=type;
		new->parent=s;
		INIT_LIST_HEAD(&new->sibling_list);
		INIT_LIST_HEAD(&new->offspring_list);
		INIT_LIST_HEAD(&new->content_list);
		log("add node %s in %s\n",NODE_NAME(new),s?NODE_NAME(s):"");
		if(s)
			list_add_tail(&new->sibling_list, &s->offspring_list);
	}	
	return new;
}
/*
	0  --nok
	1 ---ok
*/
int isValidName(char* name){
    int i=0;
	for(i=0;i<strlen(name);i++){
	   if((name[i]!='.')&&!isdigit(name[i])&&!isalpha(name[i])){
	   	 return 0;
	   	}
	  }
	return 1;
}
int rmkdir(const char *pathname) {
	int ret=0;
	errno=EOK;
	node* parent=NULL;
	node* cur=NULL;
	char basename[MAX_NAME_LEN]={0};
	log("pathname=%s\n",pathname);
	
	cur=_find(pathname,&parent,basename);
	log("errno=%d\n",errno);
	if(errno==ENOFILE&&parent){
		addNode(parent,basename,DNODE);
		ret=0;
		errno=EOK;
	}else
		ret=-1;		
end:
	return ret;
}

int rrmdir(const char *pathname) {       
	errno=EOK;
	print("rmdir %s\n", pathname);
	node*r=find(pathname);
	if(r==root){
		errno=EACCESS;
		return -1;
	}
	if(!r){
		errno=ENOENT;
		return -1;
	}
	if(NODE_IS_FILE(r)){
		errno=ENOTDIR;
		return -1;
	}
	if(!list_empty(&r->offspring_list)){
		errno=ENOTEMPTY;
		return -1;
	}

	_close_ramfs(r);
	return 0;
}

int runlink(const char *pathname) {
	errno=EOK;
	print("runlink %s\n", pathname);
	node*r=find(pathname);
	if(r==root){
		errno=EACCESS;
		return -1;
	}
	if(!r){
		errno=ENOENT;
		return -1;
	}
	if(NODE_IS_DIR(r)){
		errno=EISDIR;
		return -1;
	}
	
	_close_ramfs(r);
	return 0;
}
void rls_dir(const char* pathname){
	show_ramfs(find(pathname),0,1);	
}
/*
	errno=ENOFILE;  //1:home[Y]/ubuntu[Y]/data.txt[N]
	errno=ENOENT;   //1:home[Y]/ubuntu[N]/data.txt
	errno=EEXIST;   //1:home[Y]/data.txt[Y] 2:/home[Y]/ubuntu[Y]
	errno=ENOTDIR;  //1:home[Y]/data.txt/123.txt
*/
node *_find(const char* pathname,node** parent,char* bname){
	int path_len=strlen(pathname);
	errno=EOK;
	node* r=NULL;
	char* _src=calloc(1,path_len+1);
	strcpy(_src,pathname);
	_src=trim(_src);
	if(_src[0]!='/'){
		// must / in header
		errno=ENOENT;
		goto end;
	}
	char* name=basename(_src);
	if(name){
			log("name=%s\n",name);
			if(strlen(name)>32){
				errno=ENAMETOOLONG;
				goto end;
			}
			if(strcmp(name,"/")){//not root dir			
				if((strlen(name)==0)||!isValidName(name)){
					errno=EINVAL;
					goto end;
				}
			}else{
				//root dir		
				errno=EEXIST;
				r=root;
				goto end;
			}
			
	}
	if(bname)
		strncpy(bname,name,MAX_NAME_LEN);
	
	char* src=calloc(1,path_len+1);
	{
		strcpy(src,pathname);		
		char *tok=strtok(src, "/");
		node* s=root;		
		while (tok!=NULL) {
			log("token=%s\n",tok);
			node* n=findNode(s,tok);
			if(!n){
				log("[Error]can't find %s\n",tok);
				char *t = strtok(NULL, "/");
				if(!t){
					//last word in src
					log("Last word %s \n",tok);
					if(parent)
						(*parent)=s;
					errno=ENOFILE;/*/home[Y]/ubuntu[Y]/data.txt[N]*/
				}else{
					//not last word
					errno=ENOENT;/*/home[Y]/ubuntu[N]/data.txt*/
				}
				break;
			}
			s=n;
			tok = strtok(NULL, "/");
			if(tok==NULL){
				//last word				
				errno=EEXIST;/*/home[Y]/data.txt[Y]*/
				r=s;				
				break;
			}else{
				if(NODE_IS_FILE(n)){
					errno=ENOTDIR;/*/home[Y]/data.txt/123.txt*/
					break;
				}
			}
		}
		free(src);
	}
end:
	if(_src)
		free(_src);
	return r;
}

node *find(const char* pathname){
	return _find(pathname,NULL,NULL);
}
/*
	0---hex
	1--- char
*/
void dump_file_content(node *r,int mode){
	if(NODE_IS_FILE(r)){
		struct list_head *p, *n;
		list_for_each_safe(p, n, &r->content_list) {
			struct CONTENT* c= list_entry(p, struct CONTENT, con_list);
			//xlog2("c->using=%d\n",c->using);
	       	dump_buffer((const unsigned char *)c->content, c->using,(mode==DUMP_FILE_HEX)?"H":"C", "");
		}
	}
	printf("\n");
}
/*
recursive -- show level x
		  if -1,forvever
*/
void show_ramfs(node *r,int showme,int level) {
	if(r){
		log("name:%s type=%s parent:%s\n",NODE_NAME(r),NODE_TYPE(r),r->parent?NODE_NAME(r->parent):" ");
		if(showme)
			printf("%s\n",NODE_NAME(r));
		if(!level)
			return;
		if(NODE_IS_DIR(r)){
			struct list_head *p, *n;
			int first=1;
			list_for_each_safe(p, n, &r->offspring_list) {
				node* c= list_entry(p, node,sibling_list );
				printf("%s%s",(first)?"":" ",NODE_NAME(c));
				first=0;				
			}
			printf("\n");
			list_for_each_safe(p, n, &r->offspring_list) {
				node* c= list_entry(p, node,sibling_list );
				show_ramfs(c,0,(level==-1)?(-1):(level-1));				
			}
		}else if(NODE_IS_FILE(r)){
			log("file size:%u\n",NODE_SIZE(r));
			dump_file_content(r,0);
		}
	}
}

void init_ramfs() {
	root=addNode(NULL,"/",DNODE);
	init_fd();
}
void free_file_content(node *r){
		if(NODE_IS_FILE(r)){
			struct list_head *p, *n;
			list_for_each_safe(p, n, &r->content_list) {
				struct CONTENT* c= list_entry(p, struct CONTENT, con_list);
				list_del(&c->con_list);
				r->size-=c->using;
				log("[Free File Content]name:%s\n",NODE_NAME(r));
		        free(c);
			}
		}
}
unsigned int file_total_space(node *r){
	unsigned int total=0;
	if(NODE_IS_FILE(r)){
			struct list_head *p, *n;
			list_for_each_safe(p, n, &r->content_list) {
				struct CONTENT* c= list_entry(p, struct CONTENT, con_list);
				total+=sizeof(c->content);
			}
	}
	return total;
}
void _close_ramfs(node *r) {
	if(r){		
		if(NODE_IS_DIR(r)){
			struct list_head *p=NULL, *n=NULL;
			list_for_each_safe(p, n, &r->offspring_list) {
				node* c= list_entry(p, node,sibling_list );
				_close_ramfs(c);
			}
		}else if(NODE_IS_FILE(r)){
			free_file_content(r);
		}
		log("[Free Node]name:%s type=%s\n",NODE_NAME(r),NODE_TYPE(r));
		list_del(&r->sibling_list);
		free(r->name);
		free(r);
	}
}
void close_ramfs() {
	log("################\n");
	//show_ramfs(root,1,-1);
	_close_ramfs(root);
	root=NULL;
}
