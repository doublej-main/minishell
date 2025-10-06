/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:45:39 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/06 16:52:28 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipes_and_ampersands(char *line, int i, int dflag)
{
	while (line[i])
	{
		if (line[i] == '&' || line[i] == '|')
		{
			if (isdel(line[i]))
				i++;
			if (line[i] == '&' || line[i] == '|')
				return (FAILURE);
		}
		else if (line[i] == '<' || line[i] == '>')
		{
			i++;
			if (isdel(line[i]))
			{
				i++;
				dflag = 1;
			}
			if ((line[i] == '<' || line[i] == '>') && dflag == 1)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static int	redirs(char *line, int i)
{
	int	count;

	count = 0;
	while (line[i])
	{
		if ((line[i + 1] && line[i] == '<' && line[i + 1] == '>')
			|| (line[i] == '>' && line[i + 1] == '<'))
			return (FAILURE);
		else if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
			return (FAILURE);
		else if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static void	quote_syntax(char *line, size_t *i)
{
	char	q;
	size_t	j;

	j = 0;
	while (line[j] != '\'' && line[j] != '"')
		j++;
	if (line[*i] == '\'' || line[*i] == '"')
	{
		*i = j;
		q = line[*i];
		*i += 1;
		while (line[*i] && line[*i] != q)
			*i += 1;
	}
}

int	syntax_error_checker(t_shell *shell, char *line)
{
	size_t	i;

	i = 0;
	if (line)
	{
		quote_syntax(line, &i);
		while (line[i])
		{
			if (!pipes_and_ampersands(line, i, 0))
			{
				ft_putstr_fd("Syntax Error\n", STDOUT_FILENO);
				shell->status = 2;
				free(line);
				return (FAILURE);
			}
			else if (!redirs(line, i))
			{
				ft_putstr_fd("Syntax Error\n", STDOUT_FILENO);
				shell->status = 2;
				free(line);
				return (FAILURE);
			}
			i++;
		}
	}
	return (SUCCESS);
}
