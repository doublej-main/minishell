#include "minishell.h"

char	*strip_quotes(t_arena *arena, const char *s)
{
	char	*out;
	int		i;
	int		j;
	char	q;

	out = arena_calloc(arena, ft_strlen(s) + 1);
	if (!out)
		return (NULL);
	i = 0;
	q = 0;
	j = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && q == 0)
			q = s[i];
		else if (q && s[i] == q)
			q = 0;
		else
			out[j++] = s[i];
		i++;
	}
	out[j] = '\0';
	return (out);
}

int	hd_open_tmp(t_arena *arena, char **path_out)
{
	static int count;
	int			tries;
	int			fd;
	char		*heap_path;

	tries = 0;
	count = 0;
	printf("in hd_open_tmp\n");
	while (tries++ < 69 && ++count)
	{
		heap_path = hd_path_heap(count, arena);
		printf("heap_path: %s\n", heap_path);
		if (!heap_path)
			return (INIT_FAIL);
		fd = open(heap_path, O_WRONLY | O_CREAT | O_EXCL, 0600);
		if (fd >= 0)
		{
			*path_out = arena_strdup(arena, heap_path);
			if (!*path_out)
			{
				close(fd);
				unlink(heap_path);
				return (INIT_FAIL);
			}
			return (fd);
		}
	}
	return (INIT_FAIL);
}

char	*hd_path_heap(unsigned int count, t_arena *arena)
{
	char	*pid_s;
	char	*count_s;
	char	*tmp;
	char	*path;

	pid_s = ft_itoa(getpid());
	if (!pid_s)
		return (NULL);
	count_s = ft_itoa(count);
	if (!count_s)
		return (free(pid_s), NULL);
	tmp = env_join("/tmp/minishell_hd_", pid_s, "_");
	free(pid_s);
	path = arena_strjoin(tmp, count_s, arena);
	if (!path)
		return (free(tmp), free(count_s), NULL);
	free(count_s);
	free(tmp);
	return (path);
}
