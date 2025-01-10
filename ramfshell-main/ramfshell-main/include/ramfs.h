#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

struct list_head {
	struct list_head *next, *prev;
};
#define offsetof(TYPE, MEMBER)	((size_t)&((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({			\
	const struct list_head *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define LIST_POISON1  ((void *) 0x11111111)
#define LIST_POISON2  ((void *) 0x22222222)
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
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
}

static inline void list_replace(struct list_head *old,
				struct list_head *new)
{
	new->next = old->next;
	new->next->prev = new;
	new->prev = old->prev;
	new->prev->next = new;
}

static inline void list_replace_init(struct list_head *old,
				     struct list_head *new)
{
	list_replace(old, new);
	INIT_LIST_HEAD(old);
}

static inline void list_swap(struct list_head *entry1,
			     struct list_head *entry2)
{
	struct list_head *pos = entry2->prev;

	list_del(entry2);
	list_replace(entry1, entry2);
	if (pos == entry1)
		pos = entry2;
	list_add(entry1, pos);
}

static inline void list_del_init(struct list_head *entry)
{
	__list_del_entry(entry);
	INIT_LIST_HEAD(entry);
}

static inline void list_move(struct list_head *list, struct list_head *head)
{
	__list_del_entry(list);
	list_add(list, head);
}

static inline void list_move_tail(struct list_head *list,
				  struct list_head *head)
{
	__list_del_entry(list);
	list_add_tail(list, head);
}

static inline int list_is_first(const struct list_head *list,
					const struct list_head *head)
{
	return list->prev == head;
}

static inline int list_is_last(const struct list_head *list,
				const struct list_head *head)
{
	return list->next == head;
}


static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

#define list_last_entry(ptr, type, member) \
	list_entry((ptr)->prev, type, member)

#define list_next_entry(pos, member) \
	list_entry((pos)->member.next, typeof(*(pos)), member)

#define list_prev_entry(pos, member) \
	list_entry((pos)->member.prev, typeof(*(pos)), member)
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

#define list_entry_is_head(pos, head, member)				\
	(&pos->member == (head))

#define list_for_each_entry(pos, head, member)				\
	for (pos = list_first_entry(head, typeof(*pos), member);	\
	     !list_entry_is_head(pos, head, member);			\
	     pos = list_next_entry(pos, member))

//#define DEBUG
#define dump(f, args...)  do {  printf(f, ##args); } while (0)
#define xlog(f, args...)  do { printf("[%-16s] [%-8d] ", __FUNCTION__, __LINE__); printf(f, ##args); } while (0)

#ifdef DEBUG
#define log(f, args...)  do { printf("[%-16s] [%-8d] ", __FUNCTION__, __LINE__); printf(f, ##args); } while (0)
#else
#define log(f, args...)  
#endif

#define O_APPEND 0x02000
#define O_CREAT 0x0100
#define O_TRUNC 0x01000
#define O_RDONLY 0x01
#define O_WRONLY 0x02
#define O_RDWR 0x04

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define EACH_CONTENT_LEN 1024
#define FD_MAX 1024
typedef struct node {
  enum { FNODE, DNODE } type;
  struct node *parent; // if DTYPE
  struct list_head sibling_list;
  struct list_head offspring_list;
  struct list_head content_list;
  int nrde;
  char *name;
  unsigned int size;
} node;

#define NODE_TYPE(r) ((r)->type==FNODE)?"File":"Dir"
#define NODE_NAME(r) ((r)->name)
#define NODE_SIZE(r) ((r)->size)

#define NODE_IS_DIR(r) ((r)->type==DNODE)
#define NODE_IS_FILE(r) ((r)->type==FNODE)
#ifndef ONLINE_JUDGE
  #define print(...) printf("\033[31m");printf(__VA_ARGS__);printf("\033[0m");
#else
  #define print(...) 
#endif

struct CONTENT{
	struct list_head con_list;
	unsigned int using;
	char content[EACH_CONTENT_LEN];
};

typedef struct FD {
  bool used;
  int offset;
  int flags;
  node *f;
} FD;

typedef intptr_t ssize_t;
typedef uintptr_t size_t;
typedef long off_t;
#define NRFD 4096

enum ERR_NO{
	EOK=0,
	ENOENT=-1,
	ENOTDIR=-2,
	EEXIST=-3,
	ENAMETOOLONG=-4,
	EINVAL=-5,
	ENFILE=-6,
	EBADF=-7,
	EISDIR=-8,
	ENOFILE=-9,
	EACCESS=-10,
	ENOTEMPTY=-11,
};
int ropen(const char *pathname, int flags);
int rclose(int fd);
ssize_t rwrite(int fd, const void *buf, size_t count);
ssize_t rread(int fd, void *buf, size_t count);
off_t rseek(int fd, off_t offset, int whence);
int rmkdir(const char *pathname);
int rrmdir(const char *pathname);
int runlink(const char *pathname);
void init_ramfs();
void close_ramfs();
node *find(const char *pathname);
node *findNode(node*s,char* name);
node* addNode(node* s,char* name,int type);
enum DUMP_FILE_MODE{
	DUMP_FILE_HEX=0,
	DUMP_FILE_CHAR
};
void dump_file_content(node *r,int);
void show_ramfs(node *r,int showme,int recursive);
extern int errno;
void init_fd();
int fetch_fd(int offset,int flags,node* n);
void free_file_content(node *r);
int isValidName(char* name);
void rls_dir(const char* pathname);
extern node *root;
node *_find(const char* pathname,node** parent,char*);
#define MAX_NAME_LEN 64
void _close_ramfs(node *r) ;
unsigned int file_total_space(node *r);
extern FD fdesc[];
void dump2Assertbuf(char *format, ... );
void clearAssertbuf();
void printAssertbuf();
extern char assertbuf[];
extern int assert_mode;
void enable_assert();
void disable_assert();
char *trim(char *str);
typedef struct Shell_Path {
  struct list_head conn_list;
  char *path;
} SHELL_PATH;
extern SHELL_PATH shell_path;

