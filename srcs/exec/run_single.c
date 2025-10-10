/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:43:54 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/10 10:50:05 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_single_parent(t_cmd *cmd, t_shell *shell)
{
	int	status;

	if (cmd->in || cmd->out)
	{
		if (io_apply_redirs(cmd) < 0)
			return (EXIT_FAILURE);
	}
	status = run_parent_builtin_cmd(cmd->argv[0], cmd->argv, shell);
	if (cmd->in || cmd->out)
		io_restore_std(shell->fd_in, STDOUT_FILENO);
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
	int		i;
	pid_t	pid;

	i = 0;
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (cmd->in || cmd->out)
			if (io_apply_redirs(cmd) < 0)
				_exit(1);
		exec_external_or_builtin(cmd, shell);
	}
	return (wait_one(pid));
}

int	run_single(t_cmd *cmd, t_shell *shell)
{
	if (cmd->argv && cmd->argv[0] && is_parent_builtin(cmd->argv[0]))
		return (run_single_parent(cmd, shell));
	if ((!cmd->argv || !cmd->argv[0]) && !cmd->in && !cmd->out)
		return (126);
	return (fork_one_child(cmd, shell));
}
