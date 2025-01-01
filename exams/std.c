#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define maxSLen 10004
#define maxstLen 102
#define Malloc(type, size) (type *)malloc((size) * sizeof(type))
typedef struct node
{
	char ch;
	struct node *next;
} node;

typedef struct LinkList
{
	node *head, *tail;
} LinkList;

typedef struct rule
{
	char *s, *t;
} rule;

void printNode(node *head)
{
	node *cur = head;
	while (cur)
	{
		putchar(cur->ch);
		cur = cur->next;
	}
	putchar('\n');
}

LinkList createLinkList(char *str)
{
	LinkList list;
	list.head = Malloc(node, 1);
	node *cur = list.head;
	char *ptr = str;
	while (1)
	{
		cur->ch = *ptr;
		ptr++;
		if (*ptr == '\0')
		{
			list.tail = cur;
			break;
		}
		cur->next = Malloc(node, 1);
		cur = cur->next;
	}
	return list;
}

void frees(node *s, int ls)
{
	while (ls-- && s)
	{
		// printf("%c", s->ch);
		node *cur = s;
		s = s->next;
		free(cur);
	}
	// putchar('\n');
}
int mm = 0;
void replace(LinkList list, rule r)
{
	node *cur = list.head;
	int ls = strlen(r.s);
	while (cur->next)
	{
		bool match = false;
		node *S = cur->next;
		char *s = r.s;
		while (S != NULL)
		{
			if (*s == '\0')
			{
				match = true;
				break;
			}
			if (S->ch != *s)
				break;
			S = S->next;
			s++;
		}
		match = !*s;
		if (match)
		{
			mm++;
			LinkList t = createLinkList(r.t);
			frees(cur->next, ls);
			cur->next = t.head;
			t.tail->next = S;
			cur = t.tail;
		}
		else
			cur = cur->next;
	}
}

void transformation(LinkList list, rule R[], int n)
{
	for (int i = 0; i < n; i++)
		replace(list, R[i]);
}

int main(void)
{
	char *str = Malloc(char, maxSLen);
	scanf("%s", str + 1);
	LinkList list = createLinkList(str);
	rule R[100];
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		R[i].s = Malloc(char, maxstLen);
		R[i].t = Malloc(char, maxstLen);
		scanf("%s%s", R[i].s, R[i].t);
	}
	while (m--)
		transformation(list, R, n);
	printNode(list.head->next);
	// printf("%d\n", mm);
	return 0;
}