#include "minishell.h"

static void	early_exit(t_shell *shell)
{
	ft_putstr_fd("command not found\n", 2);
	shell_destroy(shell);
	_exit(127);
}

static void	cleanup_child(t_shell *shell, char **envv, char *prog)
{
	ft_free(envv);
	free(prog);
	shell_destroy(shell);
	if (errno == EACCES)
		_exit(126);
	else
		_exit(127);
	shell_destroy(shell);
}

void	exec_external_or_builtin(const t_cmd *cmd, t_shell *shell)
{
	char	**envv;
	char	*prog;
	int		status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		_exit(0);
	if (is_any_builtin(cmd->argv[0]))
	{
		status = run_any_builtin(cmd->argv[0], cmd->argv, shell);
		shell_destroy(shell);
		_exit(status);
	}
	prog = NULL;
	if (ft_strchr(cmd->argv[0], '/'))
		prog = ft_strdup(cmd->argv[0]);
	else
		prog = path_search(cmd->argv[0], shell->env);
	if (!prog)
		early_exit(shell);
	envv = env_to_chars(shell->env);
	if (!envv)
		_exit(1);
	execve(prog, cmd->argv, envv);
	cleanup_child(shell, envv, prog);
}

int	execute_pipeline(t_pl *pl, t_shell *shell)
{
	int	status;

	if (heredoc_prepare_all(shell) < 0)
	{
		dup2(shell->fd_in, STDIN_FILENO);
		return (130);
	}
	if (!shell->pipe_head->next)
		status = run_single(shell->pipe_head->cmd, shell);
	else
		status = run_pipeline(shell->pipe_head, shell);
	heredoc_cleanup_all(pl);
	return (status);
}
