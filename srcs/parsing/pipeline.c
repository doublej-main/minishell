/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:46:15 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/07 13:29:40 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_segment(t_shell *shell, t_pl *pipeblock, t_token *tok)
{
	pipeblock->cmd = arena_alloc(shell->arena, sizeof(t_cmd));
	if (!pipeblock->cmd)
		return (FAILURE);
	pipeblock->cmd->in = arena_calloc(shell->arena, sizeof(t_redir));
	if (!pipeblock->cmd->in)
		return (FAILURE);
	pipeblock->cmd->out = arena_calloc(shell->arena, sizeof(t_redir));
	if (!pipeblock->cmd->out)
		return (FAILURE);
	pipeblock->cmd->ac = argc(tok);
	pipeblock->cmd->argv
		= arena_alloc(shell->arena, sizeof(char *) * (pipeblock->cmd->ac + 1));
	if (!pipeblock->cmd->argv)
		return (FAILURE);
	pipeblock->cmd->argv[0] = NULL;
	return (SUCCESS);
}

void	redirs_quoted(t_token *current, t_pl *pb, char *next, t_shell *shell)
{
	t_redir	*node;
	size_t	len;

	node = add_redir(shell);
	if (!node)
		return ;
	node->type = current->type;
	node->target = next;
	len = ft_strlen(next);
	if (len >= 2 && next[0] == '\'' && next[len - 1] == '\'')
		node->quoted = 1;
	else if (len >= 2 && next[0] == '"' && next[len - 1] == '"')
		node->quoted = 2;
	else
		node->quoted = 0;
	if (current->type == REDIR_IN || current->type == REDIR_HEREDOC)
		ft_lstadd_back_redir(&pb->cmd->in, node);
	else
		ft_lstadd_back_redir(&pb->cmd->out, node);
}

char	*def_argv(t_arena *arena, char *value)
{
	char	*temp;

	temp = arena_strdup(arena, value);
	if (!temp)
		return (NULL);
	return (temp);
}

int	def_pipeblock(t_shell *shell, t_pl *pipeblock, t_token *curr, int i)
{
	while (curr)
	{
		if (curr->type == PIPE)
		{
			if (!pipeblock_helper(&pipeblock, shell, curr, i))
				return (FAILURE);
			i = 0;
		}
		else if (curr->type >= REDIR_IN && curr->type <= REDIR_HEREDOC)
		{
			if (!curr->next || curr->next->type != WORD)
				return (FAILURE);
			redirs_quoted(curr, pipeblock, curr->next->value, shell);
			curr = curr->next;
			if (curr->next)
				curr = curr->next;
			continue ;
		}
		else if (curr->type == WORD)
			i = argv_builder(pipeblock, shell, curr, i);
		curr = curr->next;
	}
	pipeblock->cmd->argv[i] = NULL;
	return (SUCCESS);
}

int	pipeline_init(t_shell *shell, t_pl **pipeblock)
{
	t_token	*curr;

	curr = shell->head;
	(*pipeblock) = arena_alloc(shell->arena, sizeof(t_pl));
	if (!*pipeblock)
		return (ft_putstr_fd("error: pipeblock\n", 2), FAILURE);
	(*pipeblock)->cmd = arena_alloc(shell->arena, sizeof(t_cmd));
	if (!(*pipeblock)->cmd)
		return (ft_putstr_fd("error: cmds\n", 2), FAILURE);
	(*pipeblock)->cmd->ac = argc(shell->head);
	(*pipeblock)->cmd->argv = arena_alloc(shell->arena,
			((*pipeblock)->cmd->ac + 1) * sizeof(char *));
	if (!(*pipeblock)->cmd->argv)
		return (ft_putstr_fd("error: bad args\n", 2), FAILURE);
	ft_lstadd_back_pipe(&shell->pipe_head, *pipeblock);
	(*pipeblock)->cmd->in = NULL;
	(*pipeblock)->cmd->out = NULL;
	if (!def_pipeblock(shell, *pipeblock, curr, 0))
	{
		shell->status = 2;
		arena_reset(shell, shell->arena);
		return (ft_putstr_fd("error: def_pipeblock\n", 2), FAILURE);
	}
	return (SUCCESS);
}
