/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:43:31 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/10 11:17:11 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_segments(t_pl *pl)
{
	int	count;

	count = 0;
	while (pl)
	{
		count++;
		pl = pl->next;
	}
	return (count);
}

static void	child_segment(t_pl *seg, t_fd *fd, t_shell *shell)
{
	if (!seg->cmd)
		even_earlier_exit(shell, 0);
	signals_default();
	if ((!seg->cmd->argv || !seg->cmd->argv[0]) && seg->cmd->out)
	{
		if (open_out(seg->cmd->out) < 0)
			even_earlier_exit(shell, 1);
		even_earlier_exit(shell, 0);
	}
	if (fd->prev_in != -1 && !(seg->cmd->in && seg->cmd->in->target))
	{
		dup2(fd->prev_in, STDIN_FILENO);
		close(fd->prev_in);
	}
	if (fd->out_fd != -1)
	{
		dup2(fd->out_fd, STDOUT_FILENO);
		close(fd->out_fd);
	}
	if (io_apply_redirs(seg->cmd) < 0)
		even_earlier_exit(shell, 1);
	exec_external_or_builtin(seg->cmd, shell);
}

static int	wait_children_last_status(void)
{
	int	status;
	int	last;

	last = 0;
	while (wait(&status) > 0)
	{
		last = status;
	}
	if (WIFSIGNALED(last))
		return (128 + WTERMSIG(last));
	return (WEXITSTATUS(last));
}

static int	fork_segment(t_pl *seg, t_fd *fd, int i, t_shell *shell)
{
	pid_t	pid;

	if (i < fd->count -1)
	{
		if (pipe(fd->fd) < 0)
			return (perror("pipe"), EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork"), EXIT_FAILURE);
	if (pid == 0)
	{
		if (i < fd->count - 1)
			close(fd->fd[0]);
		fd->out_fd = -1;
		if (i < fd->count -1)
			fd->out_fd = fd->fd[1];
		child_segment(seg, fd, shell);
		even_earlier_exit(shell, 1);
	}
	if (fd->prev_in != -1)
		close(fd->prev_in);
	if (i < fd->count -1)
		close(fd->fd[1]);
	return (EXIT_SUCCESS);
}

int	run_pipeline(t_pl *pl, t_shell *shell)
{
	t_pl		*cur;
	t_fd		fd;
	int			i;

	i = 0;
	cur = pl;
	fd.count = count_segments(pl);
	fd.prev_in = -1;
	while (i < fd.count)
	{
		if (fork_segment(cur, &fd, i, shell))
			return (EXIT_FAILURE);
		if (i < fd.count - 1)
			fd.prev_in = fd.fd[0];
		cur = cur->next;
		i++;
	}
	return (wait_children_last_status());
}
