
#include "minishell.h"

int	quote_handler(char c, int *q_flag)
{
	if (c == '\'' && *q_flag == 0)
	{
		*q_flag = 1;
		return (1);
	}
	if (c == '"' && *q_flag == 0)
	{
		*q_flag = 2;
		return (1);
	}
	if (c == '\'' && *q_flag == 1)
	{
		*q_flag = 0;
		return (1);
	}
	if (c == '"' && *q_flag == 2)
	{
		*q_flag = 0;
		return (1);
	}
	if (c == '\0' && *q_flag != 0)
		return (-1);
	return (1);
}

size_t	wdcount(const char *s, t_parser *p)
{
	size_t  i;
	size_t  count;

	i = 0;
	count = 0;
	p->q_flag = 0;
	if (!s && !s[i])
		return (0);
	while (isdel(s[i]))
		i++;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (quote_handler(s[i], &p->q_flag) < 0)
				ft_putstr_fd("quote handler failure\n", 2);
		}
		else if (isdel(s[i]) && p->q_flag == 0)
		{
			count++;
		}
		i++;
	}
	count++;
	return(count);
}

int	isdel(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r'
		|| c == '\f' || c == '\n')
		return (1);
	return (0);
}

void	parser_helper(t_parser *p, int type)
{
	if (type == 0)
	{
		p->del_flag = 1;
		p->start = p->i;
	}
	else if (type == 1)
	{
		p->del_flag = 0;
		p->start = -1;
		p->j++;
	}
	else
	{
		p->i = 0;
		p->j = 0;
		p-> start = -1;
		p->del_flag = 0;
		p->q_flag = 0;
	}
}
