#include "minishell.h"

static int	heredoc_prepare_one(t_shell *shell, t_redir *r)
{
	char	*delim;
	char	*path;
	int		fd;

	printf("prepare one\n");
	if (shell->pipe_head->cmd->in->quoted)
		delim = strip_quotes(shell->arena, r->target);
	else
		delim = arena_strdup(shell->arena, r->target);
	if (!delim)
		return (INIT_FAIL);
	fd = hd_open_tmp(shell->arena, &path);
	if (hd_loop(fd, delim) < 0)
	{
		close(fd);
		unlink(path);
		return (INIT_FAIL);
	}
	close(fd);
	r->type = REDIR_IN;
	r->target = path;
	r->hd_tmp = 1;
	return (SUCCESS);
}

int	heredoc_prepare_all(t_shell *shell)
{
	t_pl	*seg;
	t_redir	*r;

	printf("prepare all\n");
	if (!shell->pipe_head->cmd->in)
		return (SUCCESS);
	seg = shell->pipe_head;
	printf("%d\n", seg->cmd->in->type);
	while (seg)
	{
		printf("inside loop\n");
		if (seg->cmd->in->target)
			r = seg->cmd->in;
		while (r)
		{
			if (r->type == REDIR_HEREDOC)
			{
				printf("fails here\n");
				if (heredoc_prepare_one(shell, r) < 0)
					return (INIT_FAIL);
			}
			r = r->next;
		}
		seg = seg->next;
	}
	return (SUCCESS);
}

void	heredoc_cleanup_all(t_pl *pl)
{
	t_pl *seg;
	t_redir *r;

	if (!pl->cmd->in->target)
		return ;
	seg = pl;
	while (seg)
	{
		if (seg->cmd->in->target)
			r = seg->cmd->in;
		while (r)
		{
			if (r->type == REDIR_IN && r->hd_tmp == 1 && r->target)
				unlink(r->target);
			r = r->next;
		}
		seg = seg->next;
	}
}