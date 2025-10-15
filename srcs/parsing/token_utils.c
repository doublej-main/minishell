/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:46:56 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/15 12:09:22 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_env(t_shell *shell, char **str)
{
	char	*itoa;
	int		len;
	int		dol_count;

	if (only_dollars(*str))
		return (SUCCESS);
	len = ft_strlen(*str);
	itoa = NULL;
	if (ft_strchr(*str, '$') && (*str)[0] != '\'' && (*str)[len - 1] != '\'')
	{
		dol_count = 0;
		dol_count = count_expanse(*str);
		while (dol_count > 0)
		{
			*str = spliceline(shell, *str, NULL);
			dol_count--;
		}
		if (!*str)
			return (FAILURE);
	}
	return (SUCCESS);
}

t_token	*add_token(t_shell *shell)
{
	t_token	*temp;

	temp = arena_alloc(shell->arena, sizeof(*temp));
	if (!temp)
		return (NULL);
	temp->value = NULL;
	temp->type = 0;
	temp->next = NULL;
	return (temp);
}

int	tokenization_helper(t_shell *shell, t_parser *p, t_token *token, int i)
{
	char	*val;

	token = add_token(shell);
	val = check_for_shell_status(shell, p->array[i]);
	if (val)
		token->value = val;
	else
		token->value = arena_strdup(shell->arena, p->array[i]);
	if (!token->value)
		return (ft_putstr_fd("error: token\n", 2), FAILURE);
	token->type = get_type(token->value);
	ft_lstadd_back(&shell->head, token);
	return (SUCCESS);
}

int	syntax_compare(char *token, char *next)
{
	if (((ft_strcmp(token, "<") == 0)
			|| (ft_strcmp(token, ">") == 0)
			|| (ft_strcmp(token, ">>") == 0)
			|| (ft_strcmp(token, "<<") == 0))
		&& ((!next)
			|| (ft_strcmp(next, "<") == 0)
			|| (ft_strcmp(next, ">") == 0)
			|| (ft_strcmp(next, ">>") == 0)
			|| (ft_strcmp(next, "<<") == 0)))
		return (FAILURE);
	else if (((ft_strcmp(token, "&") == 0) || (ft_strcmp(token, "|") == 0))
		&& ((ft_strcmp(next, "&") == 0) || ft_strcmp(next, "|") == 0))
		return (FAILURE);
	return (SUCCESS);
}

int	syntax_helper(char *token)
{
	size_t	i;

	i = 0;
	while (token[i])
	{
		if ((token[i] == '&' || token[i] == '|')
			&& (token[i + 1] == '&' || token[i + 1] == '|'))
			return (FAILURE);
		else if ((token[i] == '<' && token[i + 1] == '>')
			|| (token[i] == '>' && token[i + 1] == '<'))
			return (FAILURE);
		else if (token[i] == '<' || token[i] == '>'
			|| token[i] == '&' || token[i] == '|')
		{
			if (token[i + 1] && (token[i + 1] == '<' || token[i + 1] == '>'
					|| token[i + 1] == '&' || token[i + 1] == '|'))
				if (token[i + 2] && (token[i + 2] == '<' || token[i + 2] == '>'
						|| token[i + 2] == '&' || token[i + 2] == '|'))
					return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
