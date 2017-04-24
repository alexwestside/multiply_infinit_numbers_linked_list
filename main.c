
/**********************************************************************************************************************
* Hello!
 *
************************VERSION #1************************************************************************************
 *
* This is VERSION #1 of program which solves task by implementation linked list.
 * It was be first thought about implementation solve algorithm.
 * Below you can find VERSION #2 solves by using array of integer.
 *
**********************************************************************************************************************
 * Program takes 2 parameters which can be 2 txt files with a "infinit" numbers.
* That numbers will be multiply and write a result to the created file.
 *
**********************************************************************************************************************
 * Thank you for watching the code!
 * If you have interest to review my other projects,
 * please follow the link - https://gitlab.com/users/sklif.85/projects.
**********************************************************************************************************************
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

/**
 * Define a structure which will be fill a int representation number sequence of the result
 */

typedef struct s_list
{
	int num;
	struct s_list *next;
	struct s_list *prev;
} t_list;

/**
 * Handling  possible errors
 */

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

/**
 * The function return given string in reverse direction
 */

char *revstr(char *str)
{
	char *s;
	size_t len;

	len = strlen(str);
	s = (char *)malloc(sizeof(char) * len + 1);
	s[len] = '\0';
	while (*str && len--)
	{
		s[len] = *str;
		str++;
	}
	return (s);
}

/**
 * The function convert character to integer
 */

int atoi_char(char c)
{
	int num = 0;
	num = c - '0';
	return (num);
}

/**
 * The function takes two stings and pointer to linked list.
 * The main idea is a make linked list and
 * fill it by the integers in each step of algorithm "multiplication by a column".
 */

void mult_infinit(t_list **res, char *s1, char *s2)
{
	char *str1;
	char *str2;
	t_list *list;
	t_list *move;
	int num;

	str2 = s2;
	*res = (t_list *) malloc(sizeof(t_list));
	(*res)->prev = NULL;
	(*res)->next = NULL;
	(*res)->num = 0;
	list = *res;
	move = *res;
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
					list->next = (t_list *) malloc(sizeof(t_list));
					list->next->next = NULL;
					list->next->prev = list;
					list->next->num = (list->num + num) / 10;
					list->num = (list->num + num) % 10;
				}
				else
				{
					if ((list->next->num + ((list->num + num) / 10)) >= 10)
					{
						list->next->next = (t_list *) malloc(sizeof(t_list));
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
				list->next = (t_list *) malloc(sizeof(t_list));
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

/**
 * The function opens and reads the given file by a received path from the arguments.
 */

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

/**
 * The function get result list and write answer to the created and opened file.
 */

void print_answer(t_list *res)
{
	FILE *fp = NULL;
	fp = fopen("result.txt", "w");
	t_list *list;

	if (fp)
	{
		list = res;
		while (list->next)
			list = list->next;
		while (list)
		{
			if (!list->next && !list->num)
				list = list->prev;
			else
			{
				fprintf(fp, "%d", list->num);
				list = list->prev;
			}
		}
	}
	else
		ft_error(2);
	fclose(fp);
}

/**
 * Entry point
 */

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

/*********************************************************************************************************************/
/*********************************************************************************************************************/
/***********************VERSION #2************************************************************************************/

/*
#include <fstream>

using namespace std;

void ft_error(int id)
{
	if (id == 1)
	{
		std::cout << "Please give me 2 files!";
		exit(0);
	}
	if (id == 2)
	{
		std::cout << "Can't open FILE!";
		exit(0);
	}
	if (id == 3)
	{
		std::cout << "Can't allocate MEMORY!";
		exit(0);
	}
}

void print_answer(int *arr, int len)
{
	ofstream result;
	result.open("result.txt");
	while (len)
	{
		if (arr[len - 1] == 0)
		{
			len--;
			continue;
		}
		else
			break ;
	}
	while (len > 0)
	{
		result << arr[len - 1];
		len--;
	}
	result.close();
}

int atoi_char(char c)
{
	int num = 0;
	num = c - '0';
	return (num);
}

void mult_infinit(int *arr, char *s1, char *s2, size_t len)
{
	int i;
	int j;
	int k;
	int num;
	int n;
	size_t len1;
	size_t len2;
	size_t sl1;
	size_t sl2;

	i = -1;
	n = 0;
	len1 = s1[strlen(s1) - 1] == '\n' ? strlen(s1) - 1 : strlen(s1);
	len2 = s1[strlen(s2) - 1] == '\n' ? strlen(s2) - 1 : strlen(s2);
	sl2 = len2 - 1;
	while (++i < len1)
	{
		j = -1;
		k = n;
		sl1 = len1 - 1;
		while (++j < len2)
		{
			num = atoi_char(s1[sl1]) * atoi_char(s2[sl2]);
			if (arr[k] + num >= 10)
			{
				if ((arr[k + 1] + (arr[k] + num) / 10) >= 10)
				{
					arr[k + 2] = (arr[k + 1] + (arr[k] + num) / 10) / 10;
					arr[k + 1] = (arr[k + 1] + (arr[k] + num) / 10) % 10;
				}
				else
				{
					arr[k + 1] = arr[k + 1] + (arr[k] + num) / 10;
					arr[k] = (arr[k] + num) % 10;
				}
			}
			else
				arr[k] = arr[k] + num;
			k++;
			sl1--;
		}
		n++;
		sl2--;
	}
	print_answer(arr, len);
}

void read_file(char **str, char *path)
{
	FILE *fp;
	size_t len = 0;

	fp = fopen(path, "r");
	if (fp)
		getline(&(*str), &len, fp);
	else
		ft_error(2);
}

int main(int ac, char **av)
{
	char *s1;
	char *s2;
	size_t len;
	int *arr;

	if (ac == 3)
	{
		read_file(&s1, av[1]);
		read_file(&s2, av[2]);
		len = strlen(s1) + strlen(s2);
		if (!(arr = (int *) malloc(sizeof(int) * len)))
			ft_error(3);
		bzero(arr, len * sizeof(int));
		mult_infinit(arr, s1, s2, len);
	}
	else
		ft_error(1);
}
*/

/*********************************************************************************************************************/