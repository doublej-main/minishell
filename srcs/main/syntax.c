#include "minishell.h"

int	syntax_error_checker(char *line)
{
	size_t	i;

	i = 0;
	if (line)
	{
		while (line[i])
		{
			if (line[i + 1] && ((line[i] == '&' && line[i + 1] == '&')
					|| (line[i] == '|' && line[i + 1] == '|')
					|| (line[i] == '<' && line[i + 1] == '>')
					|| (line[i] == '>' && line[i + 1] == '<')
					|| (line[i] == '>' && line[i + 1] == '>' && line[i + 2]
						&& line[i + 2] == '>')
					|| (line[i] == '<' && line[i + 1] == '<' && line[i + 2]
						&& line[i + 2] == '<')))
			{
				ft_putstr_fd("Syntax Error\n", STDOUT_FILENO);
				free(line);
				return (1);
			}
			i++;
		}
	}
	return (0);
}
