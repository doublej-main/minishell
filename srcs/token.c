/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:52:41 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/09/01 12:21:01 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static e_token_type	get_type(char *token)
{
	if (ft_strncmp(token,  "|", 1) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(token, "<", 1) == 0)
		return (TOKEN_REDIR_IN);
	else if (ft_strncmp(token, ">" , 1) == 0)
		return (TOKEN_REDIR_OUT);
	else if (ft_strcmp(token, ">>", 2) == 0)
		return (TOKEN_REDIR_APPEND);
	else if (ft_strncmp(token, "<<", 2) == 0)
		return (TOKEN_REDIR_HEREDOC);
	else if (ft_strncmp(token, "$", 1)
		return (TOKEN_ENV_VAR);
	else
		return (TOKEN_WORD);
}

static void	print_token(t_token *token)
{
	printf("Token: %s	| Type: %s\n", token->value, gettokentype(token->type));
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
		print_token(token);
		i++;
	}
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
