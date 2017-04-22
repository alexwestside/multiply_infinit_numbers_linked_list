
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void ft_error(int id)
{
	if (id == 1)
	{
		printf("Can't open FILE!");
		exit(0);
	}
	else if (id == 2)
	{
		printf("Can't allocate MEMORY!");
		exit(0);
	}

}

typedef struct		s_list
{
	int				num;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

char *revstr(char *str)
{
	char *s;
	size_t len;

	len = strlen(str);
	s = malloc(sizeof(char) * len + 1);
	s[len] = '\0';
	while (*str && len--)
	{
		s[len] = *str;
		str++;
	}
	return (s);
}

int atoi_char(char c)
{
	int num = 0;
	num = c - '0';
	return (num);
}

void mult_infinit(t_list **res, char *s1, char *s2)
{
	int num;
	t_list *head;
	char *p1;
	char *p2;

	p2 = s2;
	if (!((*res) = (t_list *)malloc(sizeof(t_list))))
		ft_error(2);
	(*res)->num = 0;
	(*res)->prev = NULL;
	(*res)->next = NULL;
	head = *res;
	while (*p2)
	{
		p1 = s1;
		while(*p1)
		{
			num = atoi_char(*p1) * atoi_char(*p2);
			if (((*res)->num + num) >= 10)
			{
				(*res)->num = ((*res)->num + num) % 10;
				if (!(*res)->next)
				{
					if (!((*res)->next = (t_list *) malloc(sizeof(t_list))))
						ft_error(2);
					(*res)->next->num = 0;
					(*res)->next->prev = (*res);
				}
				(*res) = (*res)->next;
				(*res)->next = NULL;
				(*res)->num = (*res)->num + num / 10;
			}
			else
			{
				(*res)->num = (*res)->num + num;
				if (!((*res)->next = (t_list *) malloc(sizeof(t_list))))
					ft_error(2);
				(*res)->next->prev = (*res);
				(*res) = (*res)->next;
				(*res)->num = 0;
				(*res)->next = NULL;
			}
			p1++;
		}
		head = head->next;
		(*res) = head;
		p2++;
	}
	(*res) = (*res)->prev;
}

void read_file(char **str, char *path)
{
	FILE *p = NULL;
	long fSize = 0;

	p = fopen(path, "r");
	if (p)
	{
		fseek(p, 0, SEEK_END);
		fSize = ftell(p);
		rewind(p);
		if (!(*str = (char *) malloc(sizeof(char) * fSize)))
			ft_error(2);
		fread(*str, 1, (size_t) fSize, p);
		if ((*str)[strlen(*str) - 1] == '\n')
			(*str)[strlen(*str) - 1] = '\0';
		fclose(p);
	}
	else
		ft_error(1);
}

void print_answer(t_list *res)
{
	FILE *p = NULL;
	p = fopen("/nfs/2016/o/orizhiy/ClionProjects/GL_task_multiply_numbers(linked_list)/result", "w");

	while (res->next)
		res = res->next;
	while (res->prev)
	{
		if (!res->next && !res->num)
			res = res->prev;
		else
		{
			fprintf(p, "%d", res->num);
			res = res->prev;
		}
	}
	fprintf(p, "%d", res->num);
}

int main()
{
	char *s1 = NULL;
	char *s2 = NULL;
	t_list *res = NULL;

	read_file(&s1, "/nfs/2016/o/orizhiy/ClionProjects/GL_task_multiply_numbers(linked_list)/test1.txt");
	read_file(&s2, "/nfs/2016/o/orizhiy/ClionProjects/GL_task_multiply_numbers(linked_list)/test2.txt");
	s1 = revstr(s1);
	s2 = revstr(s2);
	mult_infinit(&res, s1, s2);
	print_answer(res);
}
