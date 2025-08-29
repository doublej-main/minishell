/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:49:34 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/08/29 14:12:03 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token()
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

	temp = new_token();
	token->next = shell->head;
	shell->head = temp;
	return (temp);
}

char	*gettokentype(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return ("PIPE");
	else if (type == TOKEN_REDIR_IN)
		return ("REDIR IN");
	else if (type == TOKEN_REDIR_OUT)
		return ("REDIR OUT");
	else if (type == TOKEN_REDIR_APPEND)
		return ("REDIR APPEND");
	else if (type == TOKEN_REDIR_HEREDOC)
		return ("REDIR HEREDOC");
	else if (type == TOKEN_ENV_VAR)
		return ("ENV VAR");
	else
		return ("WORD");
}

size_t	wordcount(char	**array)
{
	size_t	i;
	size_t	j;
	size_t	qcount;
	size_t	count;

	i = 0;
	j = 0;
	qcount = 0;
	count = 0;
	while (array[i])
	{
		while (array[i][j])
		{
			if (array[i][j] == ''' || '"')
				qcount++;
			j++;
		}
		if (qcount % 2 == 0)
			count++;
		i++;
	}
}

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
