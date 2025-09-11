
#include "minishell.h"

static t_token_type	get_type(char *token)
{
	if (ft_strncmp(token,  "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(token, "<", 1) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(token, ">" , 1) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(token, ">>", 2) == 0)
		return (REDIR_APPEND);
	else if (ft_strncmp(token, "<<", 2) == 0)
		return (REDIR_HEREDOC);
	else if (ft_strncmp(token, "$", 1))
		return (ENV_VAR);
	else
		return (WORD);
}
//for testing
static void	print_token(t_token *token)
{
	printf("Token: %s	| Type: %s\n", token->value, gettokentype(token->type));
}

static t_token_type	get_q_type(char *token)
{
	if (token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
		return (WORD_SINGLE_Q);
	else if (token[0] == '\"' && token[ft_strlen(token) - 1] == '\"')
		return (WORD_DOUBLE_Q);
	else
		return (WORD);
}

int	isdel(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r'
		|| c == '\f' || c == '\n')
		return (1);
	return (0);
}

static char	**parser(char *line, t_arena *arena, t_parser *p)
{
	char		**array;

	p->i = 0;
	p->j = 0;
	p->start = 0;
	p->q_flag = 0;
	array = (char **){0};
	while (isdel(line[p->i]))
		p->i++;
	while (line[p->i])
	{
		if (!quote_handler(line[p->i], p))
			return (NULL);
		else if (isdel(line[p->i]) && p->q_flag == 0)
		{
			array[p->j] = arena_substr(line, p->start, p->i - p->start, arena);
			p->j++;
		}
		p->i++;
	}
	array[p->j] = 0;
	return (array);
}

int	tokenize_input(char *line, t_shell *shell)
{
	t_token		*token;
	t_parser	*p;
	size_t		i;

	i = 0;
	p = arena_alloc(shell->arena, sizeof(t_parser));
	if ((wdcount(line, p) > 0))
		p->array = arena_alloc(shell->arena, wdcount(line, p) * sizeof(char *));
	if (!p->array)
		return (perror("memory"), FAILURE);
	p->array = parser(line, shell->arena, p);
	while (p->array[i])
	{
		token = add_token(shell);
		token->value = arena_strdup(shell->arena, p->array[i]);
		if (!token->value)
			return (perror("token"), FAILURE);
		token->type = get_type(token->value);
		if (token->type == WORD)
			token->type = get_q_type(token->value);
		print_token(token);
		ft_lstadd_back(&shell->head, token);
		i++;
	}
	return (SUCCESS);
}
