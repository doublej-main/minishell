#include "minishell.h"

int	replace_with_val(char *value, t_shell *shell)
{
	t_env	*node;

	if (!ft_strcmp(value, "$?"))
	{
		shell->head->value = ft_itoa(shell->status);
		return (SUCCESS);
	}
	node = env_find(shell->env, value + 1);
	if (!node)
		return (FAILURE);
	shell->head->value = node->val;
	return (SUCCESS);
}

static void	check_for_env(t_shell *shell)
{
	t_token	*list_start;

	list_start = shell->head;
	while (shell->head)
	{
		if (shell->head->type == WORD && shell->head->value[0] == '$')
		{
			replace_with_val(shell->head->value, shell);
			shell->head = shell->head->next;
			continue ;
		}
		else
			shell->head = shell->head->next;
	}
	shell->head = list_start;
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
// for testing
// static void	print_token(t_token *token)
// {
// 	printf("Token: %s	| Type: %s\n", token->value, gettokentype(token->type));
// }

static char	**parser(char *line, t_arena *arena, t_parser *p)
{
	char		**array;

	parser_helper(p, 2);
	array = arena_alloc(arena, (wdcount(line, p) + 1) * sizeof(char *));
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
		else if (quote_handler(line[p->i], &p->q_flag) < 0)
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
	n = wdcount(line, p);
	if (n == 0)
		return (SUCCESS);
	p->array = arena_alloc(shell->arena, (n + 1) * sizeof(char *));
	if (!p->array)
		return (perror("memory"), FAILURE);
	p->array = parser(line, shell->arena, p);
	if (!p->array)
		return (perror("parser"), FAILURE);
	while (p->array[i])
	{
		if (!tokenization_helper(shell, p, token, i))
			return (perror("token"), FAILURE);
		i++;
	}
	check_for_env(shell);
	return (SUCCESS);
}
