#include "minishell.h"

static void	print_hd(t_cmd *cmd)
{
	int		fd;
	char	*gnl;

	fd = open(cmd->in->target, O_RDONLY);
	gnl = get_next_line(fd);
	while (gnl)
	{
		printf("%s", gnl);
		free(gnl);
		gnl = get_next_line(fd);
	}
}

static int	run_single_parent(t_cmd *cmd, t_shell *shell)
{
	int	status;

	if (cmd->in->target || cmd->out->target)
	{
		if (io_apply_redirs(cmd) < 0)
			return (EXIT_FAILURE);
	}
	status = run_parent_builtin_cmd(cmd->argv[0], cmd->argv, shell);
	if (cmd->in->target || cmd->out->target)
		io_restore_std(STDIN_FILENO, STDOUT_FILENO);
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
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (cmd->in->target || cmd->out->target)
		{
			if (cmd->in->hd_tmp && !cmd->argv[0])
				print_hd(cmd);
			if (io_apply_redirs(cmd) < 0)
				_exit(1);
		}
		exec_external_or_builtin(cmd, shell);
	}
	return (wait_one(pid));
}

int	run_single(t_cmd *cmd, t_shell *shell)
{
	if (cmd->argv && cmd->argv[0] && is_parent_builtin(cmd->argv[0]))
		return (run_single_parent(cmd, shell));
	return (fork_one_child(cmd, shell));
}
