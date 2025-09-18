#include "minishell.h"

static int	run_single_parent(t_cmd *cmd, t_shell *shell)
{
	int	sin;
	int	sout;
	int	status;

	sin = -1;
	sout = -1;
	if (cmd->in->target || cmd->out->target)
	{
		if (io_apply_redirs(cmd, &sin, &sout) < 0)
			return (EXIT_FAILURE);
	}
	status = run_parent_builtin_cmd(cmd->argv[0], cmd->argv, shell);
	if (cmd->in->target || cmd->out->target)
		io_restore_std(sin, sout);
	printf("%d\n", status);
	return (status);
}

static int	wait_one(pid_t pid)
{
	int	status;

	printf("waiting for exit status\n");
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
	if (pid != 0)
		printf("spawned child\n");
	if (pid == 0)
	{
		printf("child is ok\n");
		signals_default();
		printf("child is ok after signal\n");
		if (cmd->in->target || cmd->out->target)
		{
			printf("mystery shit\ncmd->in->target: %s\n cmd->out->target is: %s\n", cmd->in->target, cmd->out->target);
			if (io_apply_redirs(cmd, &sin, &sout) < 0)
				_exit(1);
		}
		printf("before exec or builtin\n");
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

	printf("run single\n%s\n", cmd->argv[0]);
	if (cmd->argv && cmd->argv[0] && is_parent_builtin(cmd->argv[0]))
		return (run_single_parent(cmd, shell));
	return (fork_one_child(cmd, shell));
}