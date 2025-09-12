#include "minishell.h"

int	mini_pwd(void)
{
	char	buf[4096];
	char	*cwd;

	cwd = getcwd(buf, sizeof(buf));
	if (!cwd)
		return (perror("pwd"), EXIT_FAILURE);
	ft_putstr(cwd);
	ft_putchar('\n');
	return (EXIT_SUCCESS);
}
