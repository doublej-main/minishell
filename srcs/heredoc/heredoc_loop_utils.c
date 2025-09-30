#include "minishell.h"

char	*hd_expander_handler(t_shell *shell, char *line)
{
	char	*key;

	if (ft_strchr(line, '$'))
	{
		key = findkey(shell, line);
		if (key)
			return (spliceline(shell, key, line, 0));
	}
	return (NULL);
}
