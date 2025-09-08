#include "minishell.h"

int	mini_cd(char **argv, t_shell *shell)
{
	char	buf[4096];
	char	*dir;
	char	*old;

	dir = argv[1];
	if (!dir)
	{
		dir = get_env(shell->env, "HOME"); //TODO
		if (!dir || !*dir)
			return (perror("cd: HOME not set\n"), EXIT_FAILURE);
	}
	old = getcwd(buf, sizeof(buf));
	if (chdir(dir) < 0)
		return (perror("cd"), EXIT_FAILURE);
	if (old)
		set_env_pair(shell, "OLDPWD", old); //TODO
	if (getcwd(buf, sizeof(buf)))
		set_env_pair(shell, "PWD", buf); //TODO
	return (EXIT_SUCCESS);
}
