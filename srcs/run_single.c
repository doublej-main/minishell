#include "minishell.h"

static int	run_single_parent(t_cmd *cmd, t_shell *shell)
{
	int	sin;
	int	sout;
	int	status;

	if (io_apply_redirs(cmd, &sin, &sout) < 0)
		return (EXIT_FAILURE);
	status = run_parent_builtin_cmd(cmd->argv[0], cmd->argv, shell);
	io_restore_std(sin, sout);
	return (status);
}

static int	wait_one(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
		return (perror("waitpid"), EXIT_FAILURE);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (SUCCESS);
}

static int	fork_one_child(t_cmd *cmd, t_shell *shell)
{
	int		sin;
	int		sout;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		signals_default();
		if (io_apply_redirs(cmd, &sin, &sout) < 0)
			_exit(1);
		exec_external_or_builtin(cmd, shell);
	}
	return (wait_one(pid));
}

int	run_single(t_cmd *cmd, t_shell *shell)
{
	// int sin;
	// int sout;
	// pid_t pid;
	// int status;

	if (cmd->argv && cmd->argv[0] && is_parent_builtin(cmd->argv[0]))
		return (run_single_parent(cmd, shell));
	return (fork_one_child(cmd, shell));
}