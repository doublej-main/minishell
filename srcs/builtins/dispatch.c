#include "minishell.h"

int	is_any_builtin(const char *name)
{
	if (!name)
		return (FAILURE);
	return (!ft_strcmp(name, "echo") || !ft_strcmp(name, "pwd")
		|| !ft_strcmp(name, "cd") || !ft_strcmp(name, "export")
		|| !ft_strcmp(name, "unset") || !ft_strcmp(name, "env")
		|| !ft_strcmp(name, "exit"));
}

int	is_parent_builtin(const char *name)
{
	if (!name)
		return (FAILURE);
	return (!ft_strcmp(name, "cd") || !ft_strcmp(name, "export")
		|| !ft_strcmp(name, "unset") || !ft_strcmp(name, "exit"));
}

int	run_any_builtin(const char *name, char **argv, t_shell *shell)
{
	if (!ft_strcmp(name, "echo"))
		return (mini_echo(argv));
	if (!ft_strcmp(name, "pwd"))
		return (mini_pwd());
	if (!ft_strcmp(name, "env"))
		return (mini_env(shell));
	if (!ft_strcmp(name, "cd"))
		return (mini_cd(argv, shell));
	if (!ft_strcmp(name, "export"))
		return (mini_export(argv, shell));
	if (!ft_strcmp(name, "unset"))
		return (mini_unset(argv, shell));
	if (!ft_strcmp(name, "exit"))
		return (mini_exit(argv, shell));
	return (SUCCESS);
}

int	run_parent_builtin_cmd(const char *name, char **argv, t_shell *shell)
{
	if (!ft_strcmp(name, "cd"))
		return (mini_cd(argv, shell));
	if (!ft_strcmp(name, "export"))
		return (mini_export(argv, shell));
	if (!ft_strcmp(name, "unset"))
		return (mini_unset(argv, shell));
	if (!ft_strcmp(name, "exit"))
		return (mini_exit(argv, shell));
	return (run_any_builtin(name, argv, shell));
}
