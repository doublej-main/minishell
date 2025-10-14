/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:44:15 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/14 15:04:44 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_prepare_one(t_shell *shell, t_redir *r)
{
	char	*delim;
	char	*path;
	int		fd;

	delim = strip_quotes(shell->arena, r->target);
	if (!delim)
		return (INIT_FAIL);
	fd = hd_open_tmp(shell->arena, &path);
	if (fd < 0)
		return (INIT_FAIL);
	if (hd_loop(fd, delim, shell, !r->quoted) < 0)
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

	seg = shell->pipe_head;
	while (seg)
	{
		r = NULL;
		if (seg->cmd->in)
			r = seg->cmd->in;
		while (r)
		{
			if (r->type == REDIR_HEREDOC)
			{
				if (heredoc_prepare_one(shell, r) < 0)
					return (INIT_FAIL);
				seg->cmd->in->target = r->target;
			}
			r = r->next;
		}
		seg = seg->next;
	}
	return (SUCCESS);
}

void	heredoc_cleanup_all(t_pl *pipeblock)
{
	t_pl	*seg;
	t_redir	*r;

	r = NULL;
	if (!pipeblock->cmd->in)
		return ;
	seg = pipeblock;
	while (seg)
	{
		if (seg->cmd->in && seg->cmd->in->target)
			r = seg->cmd->in;
		while (r)
		{
			if (r->type == REDIR_IN && r->hd_tmp == 1 && r->target)
			{
				unlink(r->target);
				r->hd_tmp = 0;
			}
			r = r->next;
		}
		seg = seg->next;
	}
}
