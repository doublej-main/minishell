#include "minishell.h"

static int	hd_write(int fd, char *line, t_shell *shell, int expand)
{
	char	*out;

	if (expand && ft_strchr(line, '$'))
		out = spliceline(shell, line);
	else
		out = arena_strdup(shell->arena, line);
	if (!out)
		return (INIT_FAIL);
	ft_putstr_fd(out, fd);
	write(fd, "\n", 1);
	return (SUCCESS);
}

static char	*findkey(t_shell *shell, char *line)
{
	int		i;
	char	*key;
	char	*dol;

	dol = ft_strchr(line, '$');
	if (!dol || !dol[1] || isdel(dol[1]))
		return (NULL);
	i = 1;
	while (dol[i] && !isdel(dol[i]))
		i++;
	key = arena_alloc(shell->arena, i);
	if (!key)
		return (NULL);
	ft_memcpy(key, dol + 1, i - 1);
	key[i - 1] = '\0';
	return (key);
}

char	*spliceline(t_shell *shell, char *line)
{
	const char	*dol;
	char		*key;
	const char	*val;
	const char	*post;
	char		*out;

	dol = ft_strchr(line, '$');
	if (!dol)
		return (arena_strdup(shell->arena, line));
	key = findkey(shell, line);
	if (!key)
		return (arena_strdup(shell->arena, line));
	val = env_get(shell->env, key);
	if (!val)
		val = "";
	post = dol + 1 + ft_strlen(key);
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

int	hd_loop(int fd, const char *delim, t_shell *shell, int expand)
{
	char	*line;

	signals_heredoc();
	while (1)
	{
		line = readline("heredoc> ");
		if (g_sig == SIGINT)
		{
			free(line);
			g_sig = 0;
			signals_interactive();
			return (INIT_FAIL);
		}
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
