/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:42:36 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/09/01 12:13:58 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	increment_elements(t_arr *elem, size_t	type)
{
	if (type == 0)
	{
		elem->qcount++;
		elem->w_countin_q++;
	}
	if (type == 1)
		elem->w_countin_q = 1;
	if (type == 2)
	{
		elem->qcount = 0;
		elem->w_countin_q = 0;
	}
}

static char	*joinlines(t_arr *elem, char *array, char *array2, size_t type)
{
	char	*newarray;
	t_arena	*arena;

	if (type == 0)
	{
		elem->line = ft_strjoin(array2, ' ');
		newarray = ft_strjoin(elem->line, array);
		free(elem.line);
		increment_elements(elem, 1);
		return (newarray);
	}
	if (type == 1)
	{
		elem.line = ft_strjoin(array2, ' ');
		newarray = arena_strjoin(arena, elem.line, array);
		free(elem.line);
		increment_elements(elem, 2);
		return (newarray);
	}
}

static char	*parse_tk_array(char c, char *token, char *token2, t_arr *elem)
{
	char	*array;

	array = NULL;
	if (c == '\0'
		&& elem->qcount == 1 && elem->w_countin_q == 2)
	{
		array = joinlines(&elem, token, token2, 0);
		free(token);
		free(token2);
		return (array);
	}
	else
		return;
}

static char	*build_tk_array(char c, char *token, char *token2, t_arr *elem)
{
	char	*token_array;

	token_array = NULL;
	if (c == '\0' && elem->qcount == 2 && elem->w_countin_q == 2)
	{
		token_array = joinlines(&elem, token, token2, 1);
		free(token);
		free(token2);
		if (!token_array)
			return (NULL);
		return (token_array);
	}
	else if (c == '\0' && (elem->qcount == 0 || elem->qcount == 2))
	{
		token_array = arena_alloc(arena, sizeof(char) * ft_strlen(token));
		free(token);
		if (!token_array) 
			return (NULL);
		return (token_array);
	}
	else
		return ;
}

char	**loop_token_array(char	**token, t_arr *elem, t_arena arena, size_t wc)
{
	char	**array;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	array = arena_alloc(arena, (sizeof(char *) * wc));
	if (!array)
		return (NULL);
	while (token[i])
	{
		j = 0;
		while (token[i][j])
		{
			if (token[i][j] == ''' || '"')
				increment_elements(&elem, 0);
			token = parse_tk_array(token[i][j], token[i], token[i - 1], &elem);
			array = build_tk_array(token[i][j], token[i], token[i - 1], &elem);
			j++;
		}
		if (elem->qcount == 1)
			elem->w_countin_q++;
		i++;
	}
	return (array);
}
