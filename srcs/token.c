
#include "minishell.h"

static e_token_type	get_type(char *token)
{
	if (ft_strncmp(token,  "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(token, "<", 1) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(token, ">" , 1) == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(token, ">>", 2) == 0)
		return (REDIR_APPEND);
	else if (ft_strncmp(token, "<<", 2) == 0)
		return (REDIR_HEREDOC);
	else if (ft_strncmp(token, "$", 1)
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

void	tokenize_input(char *line, DEL, t_shell *shell)
{
	t_token	*token;
	char	**token_split;
	char	**token_array;
	size_t	i;

	i = 0;
	token_split = ft_split(line, DEL);
	token_array = handle_quotes(token_split, shell->arena);
	free_array(token_split);
	while (token_array[i])
	{
		token = add_token(shell);
		token->value = arena_strdup(shell->arena, token_array[i]);
		token->type = get_type(token->value);
		if (token->type == TOKEN_WORD)
			token->type = get_q_type(token->value);
		print_token(token);
		i++;
	}
	ast_init(shell->arena, &token);
}

char	**handle_quotes(char **token_arr, t_arena *arena)
{
	size_t	wordcount;
	char	**array;

	elem.qcount = 0;
	elem.w_countin_q = 0;
	elem.line = NULL;
	wordcount = countwords(token_arr);
	array = loop_token_array(token_arr, arena->elem, arena, wordcount);
	return (array);
}
