#include "minishell.h"

int	syntax_error_checker(t_shell *shell, char *line)
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
				shell->status = 2;
				free(line);
				return (FAILURE);
			}
			i++;
		}
	}
	return (SUCCESS);
}
