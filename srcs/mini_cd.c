#include "minishell.h"

int	mini_cd(char **argv, t_shell *shell)
{
	char	buf[4096];
	char	*dir;
	char	*old;

	dir = argv[1];
	if (!dir)
	{
		dir = env_get(shell->env, "HOME");
		if (!dir || !*dir)
			return (ft_putstr_fd("cd: HOME not set\n", 2), EXIT_FAILURE);
	}
	old = getcwd(buf, sizeof(buf));
	if (chdir(dir) < 0)
		return (ft_putstr_fd("cd", 2), EXIT_FAILURE);
	if (old)
		set_new_pair(shell->env, "OLDPWD", old);
	if (getcwd(buf, sizeof(buf)))
		set_new_pair(shell->env, "PWD", buf);
	return (EXIT_SUCCESS);
}
