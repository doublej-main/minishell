
#include "minishell.h"

t_token	*new_token(t_arena *arena)
{
	t_token *new;

	new = arena_alloc(arena, sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = arena_alloc(arena, sizeof(char *));
	if (!new->value)
		return (NULL);
	new->next = NULL;
	return (new);
}

t_token	*add_token(t_shell *shell)
{
	t_token *temp;

	temp = new_token(shell->arena);
	temp->next = shell->head;
	shell->head = temp;
	return (temp);
}

char	*gettokentype(t_token_type type)
{
	if (type == PIPE)
		return ("PIPE");
	else if (type == REDIR_IN)
		return ("REDIR IN");
	else if (type == REDIR_OUT)
		return ("REDIR OUT");
	else if (type == REDIR_APPEND)
		return ("REDIR APPEND");
	else if (type == REDIR_HEREDOC)
		return ("REDIR HEREDOC");
	else if (type == ENV_VAR)
		return ("ENV VAR");
	else
		return ("WORD");
}

int quote_handler(char c, int *q_flag)
{
	if (c == '\'' && *q_flag == 0)
	{
		*q_flag = 1;
		return (1);
	}
	else if (c == '\"' && *q_flag == 0)
	{
		*q_flag = 2;
		return (1);
	}
	else if ((c == '\'' && *q_flag == 1) ||
		(c == '\"' && *q_flag == 2))
	{
		printf("we are closing the quote\n");
		*q_flag = 0;
		return (1);
	}
	else if ((c == '\0' && (*q_flag == 1 || *q_flag == 2)) ||
		(c == '\'' && *q_flag == 2) || (c == '\"' && *q_flag == 1))
		return (-1);
	else
		return (1);
}

size_t	wdcount(const char *s, t_parser *p)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	p->q_flag = 0;
	while (isdel(s[i]))
		i++;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (quote_handler(s[i], &p->q_flag) < 0)
				ft_putstr_fd("quote handler failure\n", 2);
		}
		else if (isdel(s[i]) && p->q_flag == 0)
		{
			count++;
		}
		else if (s[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}
