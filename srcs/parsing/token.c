#include "minishell.h"

int	check_for_env(t_shell *shell, char **str)
{
	if (ft_strchr(*str, '$'))
	{
		*str = spliceline(shell, *str);
		if (!*str)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	get_type(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	if (ft_strcmp(token, "<") == 0)
		return (REDIR_IN);
	if (ft_strcmp(token, ">") == 0)
		return (REDIR_OUT);
	if (ft_strcmp(token, ">>") == 0)
		return (REDIR_APPEND);
	if (ft_strcmp(token, "<<") == 0)
		return (REDIR_HEREDOC);
	if (!ft_strcmp(token, "$"))
		return (ENV_VAR);
	else
		return (WORD);
}

static char	**parser(t_shell *shell, char *line, t_arena *arena, t_parser *p)
{
	char		**array;

	if (!line || !line[0])
		return (NULL);
	parser_helper(p, 2);
	array = arena_alloc(arena, (wdcount(shell, line, p) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (p->i <= (int) ft_strlen(line))
	{
		if (!isdel(line[p->i]) && p->start < 0)
			parser_helper(p, 0);
		if ((isdel(line[p->i]) && p->q_flag == 0 && p->del_flag == 1)
			|| (line[p->i] == '\0' && !isdel(line[p->i - 1])))
		{
			array[p->j] = arena_substr(line, p->start, p->i - p->start, arena);
			parser_helper(p, 1);
		}
		else if (quote_handler(shell, line[p->i], &p->q_flag) < 0)
			return (NULL);
		p->i++;
	}
	array[p->j] = 0;
	return (array);
}

int	tokenize_input(char *line, t_shell *shell, t_token *token)
{
	t_parser	*p;
	size_t		i;
	size_t		n;

	i = 0;
	p = arena_alloc(shell->arena, sizeof(t_parser));
	if (!p)
		return (perror("parser"), FAILURE);
	n = wdcount(shell, line, p);
	if (n == 0)
		return (SUCCESS);
	p->array = arena_alloc(shell->arena, (n + 1) * sizeof(char *));
	if (!p->array)
		return (perror("memory"), FAILURE);
	p->array = parser(shell, line, shell->arena, p);
	if (!p->array)
		return (FAILURE);
	while (p->array[i])
	{
		if (!tokenization_helper(shell, p, token, i))
			return (ft_putstr_fd("error: token\n", 2), FAILURE);
		i++;
	}
	return (SUCCESS);
}
