/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:46:47 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/07 15:56:12 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_env(t_shell *shell, char **str)
{
	char	*itoa;
	int		len;

	len = ft_strlen(*str);
	itoa = NULL;
	if (!ft_strcmp(*str, "$?") || !ft_strcmp(*str, "\"$?\""))
	{
		itoa = ft_itoa(shell->status);
		*str = arena_strdup(shell->arena, itoa);
		free(itoa);
		return (SUCCESS);
	}
	if (ft_strchr(*str, '$') && (*str)[0] != '\'' && (*str)[len - 1] != '\'')
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

static int	syntax_failsafe(t_parser *p)
{
	size_t	i;

	i = 0;
	while (p->array[i])
	{
		if ((ft_strcmp(p->array[i], "|") == 0) && !p->array[i + 1])
			return (FAILURE);
		else if (!syntax_compare(p->array[i], p->array[i + 1]))
			return (FAILURE);
		else if (p->array[i][0] != '"'
			&& p->array[i][ft_strlen(p->array[i]) - 1] != '"')
		{
			if (p->array[i][0] != '\''
				|| p->array[i][ft_strlen(p->array[i]) - 1] != '\'')
			{
				if (!syntax_helper(p->array[i]))
					return (FAILURE);
			}
		}
		i++;
	}
	return (SUCCESS);
}

int	tokenize_input(char *line, t_shell *shell, t_token *token, size_t i)
{
	t_parser	*p;
	size_t		n;

	p = arena_alloc(shell->arena, sizeof(t_parser));
	if (!p)
		return (ft_putstr_fd("Parsing Error\n", 2), 1);
	n = wdcount(shell, line, p);
	if (n == 0)
		return (0);
	p->array = arena_alloc(shell->arena, (n + 1) * sizeof(char *));
	if (!p->array)
		return (ft_putstr_fd("Memory allocation failure\n", 2), 1);
	p->array = parser(shell, line, shell->arena, p);
	if (!p->array)
		return (1);
	if (!syntax_failsafe(p))
		return (ft_putstr_fd("Syntax Error\n", 2), 2);
	while (p->array[i])
	{
		if (!tokenization_helper(shell, p, token, i))
			return (ft_putstr_fd("Tokenization Failure\n", 2), 1);
		i++;
	}
	return (0);
}
