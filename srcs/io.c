#include "minishell.h"

void	io_restore_std(int save_in, int save_out)
{
	if (save_in >= 0)
	{
		dup2(save_in, STDIN_FILENO);
		close(save_in);
	}
	if (save_out >= 0)
	{
		dup2(save_out, STDOUT_FILENO);
		close(save_out);
	}
}

static int	open_out(const t_redir *r)
{
	int	fd;

	fd = -1;
	if (r->type == RT_OUT)
		fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (r->kind == RT_APPEND)
		fd = open(r->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

static int	dup_to(int fd, int to)
{
	if (dup2(fd, to) < 0)
		return (-1);
	close(fd);
	return (EXIT_SUCCESS);
}

int	io_apply_redirs(const t_cmd *cmd, int *save_in, int *save_out)
{
	int	fd;
	t_redir	*r;

	*save_in = dup(STDIN_FILENO);
	*save_out = dup(STDOUT_FILENO);
	if (*save_in < 0 || save_out < 0)
		return (perror(dup), -1);
	r = cmd->in;
	while (r)
	{
		fd = open(r->target, O_RDONLY);
		if (fd < 0 || dup_to(fd, STDIN_FILENO) < 0)
			return (perror(r->target), -1);
		r = r->next;
	}
	r = cmd->out;
	while (r)
	{
		fd = open_out(r);
		if (fd < 0 || dup_to(fd, STDOUT_FILENO) < 0)
			return (perror(r->target), -1);
		r = r->next;
	}
	return (EXIT_SUCCESS);
}
