#include "minishell.h"

static size_t	untilspace(char *line, size_t start)
{
	while (line[start])
	{
		if (line[start] == ' ' || line[start] == '\t' || line[start] == '\n'
			|| line[start] == '\v')
			break ;
		start++;
	}
	return (start);
}

static	size_t	keyloop(char *line, size_t type)
{
	size_t	i;
	size_t	start;
	size_t	len;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			start = i;
			if (type == 1)
				return (start);
			len = untilspace(line, i) - i;
		}
		i++;
	}
	return (len);
}

static char	*findkey(t_shell *shell, char *line)
{
	char	*env_v;
	t_env	*node;
	size_t	start;
	size_t	i;
	size_t	len;

	start = keyloop(line, 1);
	i = 0;
	len = 0;
	node = NULL;
	len = keyloop(line, 0);
	env_v = arena_alloc(shell->arena, len + 1);
	while (i < len)
		env_v[i++] = line[start++];
	env_v[i] = '\0';
	node = env_find(shell->env, env_v);
	if (!node)
		return (NULL);
	return (node->val);
}

static char *spliceline(t_shell *shell, char *key, char *line)
{
	char	*splicedline;
	size_t	i;
	size_t	start;
	size_t	len;

	i = 0;
	start = keyloop(line, 1);
	len = keyloop(line, 0);
	splicedline = arena_alloc(shell->arena,
	((ft_strlen(line) - len) + ft_strlen(key) + 1));
	if (!splicedline)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$')
		{
			start = i;
			break ;
		}
		splicedline[i] = line[i];
		i++;
	}
	while (*key)
		splicedline[i++] = *key++;
	while (start < untilspace(line, start))
		start++;
	while (line[start])
		splicedline[i++] = line[start++];
	splicedline[i] = '\0';
	return (splicedline);
}

int	hd_loop(int fd, const char *delim, t_shell *shell)
{
	char	*line;
	char	*key;
	char	*splicedline;

	splicedline = NULL;
	while (420)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (!shell->pipe_head->cmd->in->quoted && ft_strchr(line, '$'))
		{
			key = findkey(shell, line);
			if (key)
				splicedline = spliceline(shell, key, line);
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		if (!splicedline)
			ft_putstr_fd(line, fd);
		else
			ft_putstr_fd(splicedline, fd);
		write(fd, "\n", 1);
		free(line);
	}
	return (SUCCESS);
}
