/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:42:54 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/02 17:43:03 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	io_restore_std(int save_in, int save_out)
{
	if (save_in != 0)
	{
		dup2(save_in, STDIN_FILENO);
		close(save_in);
	}
	if (save_out != 1)
	{
		dup2(save_out, STDOUT_FILENO);
		close(save_out);
	}
}

int	open_out(const t_redir *r)
{
	int	fd;

	fd = -1;
	if (r->type == REDIR_OUT)
		fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (r->type == REDIR_APPEND)
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

int	io_apply_redirs(const t_cmd *cmd)
{
	int		fd;
	t_redir	*r;

	r = NULL;
	if (cmd->in && cmd->in->target)
		r = cmd->in;
	while (r)
	{
		fd = open(r->target, O_RDONLY);
		if (fd < 0 || dup_to(fd, STDIN_FILENO) < 0)
			return (ft_putstr_fd("in redir error\n", 2), -1);
		r = r->next;
	}
	if (cmd->out && cmd->out->target)
		r = cmd->out;
	while (r)
	{
		fd = open_out(r);
		if (fd < 0 || dup_to(fd, STDOUT_FILENO) < 0)
			return (ft_putstr_fd("open out error\n", 2), -1);
		r = r->next;
	}
	return (EXIT_SUCCESS);
}
