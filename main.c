
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void ft_error(int id)
{
	if (id == 1)
	{
		printf("Please give me 2 files!");
		exit(0);
	}
	if (id == 2)
	{
		printf("Can't open FILE!");
		exit(0);
	}
	if (id == 3)
	{
		printf("Can't allocate MEMORY!");
		exit(0);
	}
}

typedef struct s_list
{
	int num;
	struct s_list *next;
	struct s_list *prev;
} t_list;

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
	char *str1;
	char *str2;
	t_list *list;
	t_list *move;
	int num;

	str2 = s2;
	*res = (t_list *)malloc(sizeof(t_list));
	(*res)->prev = NULL;
	(*res)->next = NULL;
	(*res)->num = 0;
	list = *res;
	move = *res;
	num = 0;
	while (*str2)
	{
		str1 = s1;
		while (*str1)
		{
			num = atoi_char(*str1) * atoi_char(*str2);
			if ((list->num + num) >= 10)
			{
				if (!list->next)
				{
					list->next = (t_list *)malloc(sizeof(t_list));
					list->next->next = NULL;
					list->next->prev = list;
					list->next->num = (list->num + num) / 10;
					list->num = (list->num + num) % 10;
				}
				else
				{
					if ((list->next->num + ((list->num + num) / 10)) >= 10)
					{
						list->next->next = (t_list *)malloc(sizeof(t_list));
						list->next->next->next = NULL;
						list->next->next->prev = list->next;
						list->next->next->num = (list->next->num + ((list->num + num) / 10)) / 10;
						list->next->num = (list->next->num + ((list->num + num) / 10)) % 10;
						list->num = (list->num + num) % 10;
					}
					else
					{
						list->next->num = list->next->num + (list->num + num) / 10;
						list->num = (list->num + num) % 10;
					}
				}
			}
			else
			{
				list->num = list->num + num;
				list->next = (t_list *)malloc(sizeof(t_list));
				list->next->next = NULL;
				list->next->prev = list;
			}
			list = list->next;
			str1++;
		}
		str2++;
		move = move->next;
		list = move;
	}
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
			ft_error(3);
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
	p = fopen("/nfs/2016/o/orizhiy/ClionProjects/GL_task_multiply_numbers(linked_list)/result.txt", "w");

	t_list *list;

	list = res;
	while (list->next)
		list = list->next;
	while(list)
	{
		if(!list->next && !list->num)
			list = list->prev;
		else
		{
			fprintf(p, "%d", list->num);
//			printf("%d", list->num);
			list = list->prev;
		}
	}
}

int main(int ac, char **av)
{
	char *s1 = NULL;
	char *s2 = NULL;
	t_list *res = NULL;

	if (ac == 3)
	{
		read_file(&s1, av[1]);
		read_file(&s2, av[2]);
		s1 = revstr(s1);
		s2 = revstr(s2);
		mult_infinit(&res, s1, s2);
		print_answer(res);
	}
	else
		ft_error(1);
}


/*




*/