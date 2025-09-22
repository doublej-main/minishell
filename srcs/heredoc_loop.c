#include "minishell.h"

int	hd_loop(int fd, const char *delim)
{
	char	*line;

	while (420)
	{
		printf("heredoc_loop\n");
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free(line);
	}
	return (SUCCESS);
}
