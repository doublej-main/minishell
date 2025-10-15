/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:44:08 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/15 14:14:51 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	hd_write(int fd, char *line, t_shell *shell, int expand)
{
	char	*out;
	int		dol_count;

	if (expand && ft_strchr(line, '$'))
	{
		out = spliceline(shell, line, NULL);
		dol_count = count_expanse(out);
		while (dol_count)
		{
			out = spliceline(shell, out, NULL);
			dol_count--;
		}
	}
	else
		out = arena_strdup(shell->arena, line);
	if (!out)
		return (INIT_FAIL);
	ft_putstr_fd(out, fd);
	write(fd, "\n", 1);
	return (SUCCESS);
}

static char	*findkey(t_shell *shell, char *line, int *j)
{
	int		i;
	char	*key;
	char	*dol;

	dol = ft_strchr(line, '$');
	if (!dol || !dol[1] || isdel(dol[1]))
		return (NULL);
	*j = 0;
	while (dol[*j] == '$' || isdel(dol[*j]))
		*j += 1;
	i = *j;
	if (dol[1] == '?')
		return (arena_strdup(shell->arena, "?"));
	while (dol[i] && !isdel(dol[i]) && dol[i] != '$'
		&& dol[i] != '"' && dol[i] != '\'')
		i++;
	key = arena_alloc(shell->arena, i);
	if (!key)
		return (NULL);
	if (*j > 1)
		ft_memcpy(key, dol + *j, i - *j);
	else
		ft_memcpy(key, dol + 1, i - 1);
	key[i - *j] = '\0';
	return (key);
}

char	*spliceline(t_shell *shell, char *line, char *key)
{
	const char	*dol;
	const char	*val;
	const char	*post;
	char		*out;
	int			j;

	dol = ft_strchr(line, '$');
	if (!dol)
		return (arena_strdup(shell->arena, line));
	key = findkey(shell, line, &j);
	if (!key)
		return (arena_strdup(shell->arena, line));
	val = env_get(shell, shell->env, key);
	if (!val)
		return (NULL);
	post = dol + j + ft_strlen(key);
	out = arena_alloc(shell->arena, (size_t)((dol - line)
				+ ft_strlen(val) + ft_strlen(post) + 1));
	if (!out)
		return (NULL);
	ft_memcpy(out, line, (size_t)(dol - line));
	ft_memcpy(out + (dol - line), val, ft_strlen(val));
	ft_memcpy(out + (dol - line)
		+ ft_strlen(val), post, ft_strlen(post) + 1);
	return (out);
}

static int	hd_signal_handler(char *line)
{
	free(line);
	g_sig = 0;
	signals_interactive();
	return (0);
}

int	hd_loop(int fd, const char *delim, t_shell *shell, int expand)
{
	char	*line;

	signals_heredoc();
	while (1)
	{
		line = readline("heredoc> ");
		if (g_sig == SIGINT)
			if (!hd_signal_handler(line))
				return (INIT_FAIL);
		if (!line)
			break ;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		if (hd_write(fd, line, shell, expand) == FAILURE)
		{
			free(line);
			return (INIT_FAIL);
		}
		free(line);
	}
	return (SUCCESS);
}
