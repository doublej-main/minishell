
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

void	tokenize_input(char *line, t_shell *shell)
{
	t_token	*token;
	char	**token_split;
	t_arr	*array;
	size_t	i;

	i = 0;
	token_split = mini_split(line, DEL);
	array = arena_alloc(shell->arena, sizeof(t_arr));
	array->token_array = handle_quotes(token_split, array, shell->arena);
	free_array(token_split);
	while (array->token_array[i])
	{
		token = add_token(shell);
		token->value = arena_strdup(shell->arena, array->token_array[i]);
		token->type = get_type(token->value);
		if (token->type == WORD)
			token->type = get_q_type(token->value);
		print_token(token);
		i++;
	}
//	ast_init(shell->arena, &token);
}

char	**handle_quotes(char **token_split, t_arr *elem, t_arena *arena)
{
	size_t	wc;
	char	**array;

	elem->qcount = 0;
	elem->w_countin_q = 0;
	elem->line = NULL;
	wc = wordcount(token_split);
	array = loop_token_array(token_split, elem, arena, wc);
	return (array);
}
