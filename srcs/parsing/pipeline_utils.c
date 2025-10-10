/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:46:31 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/10 14:26:43 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quotes(char *next)
{
	int	i;
	int	count;

	if (!next || !*next)
		return (0);
	i = 0;
	count = 0;
	while (next[i])
	{
		if (next[i] == '"' || next[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

int	argc(t_token *token)
{
	int		count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == REDIR_APPEND || token->type == REDIR_HEREDOC)
		{
			token = token->next;
			if (token)
				token = token->next;
			continue ;
		}
		if (token->type == WORD)
			count++;
		token = token->next;
	}
	return (count);
}

t_pl	*add_pipeblock(t_shell *shell)
{
	t_pl	*temp;

	temp = arena_alloc(shell->arena, sizeof(*temp));
	if (!temp)
		return (NULL);
	temp->cmd = NULL;
	temp->next = NULL;
	return (temp);
}

int	pipeblock_helper(t_pl **pipeblock, t_shell *shell, t_token *cur, int i)
{
	(*pipeblock)->cmd->argv[i] = NULL;
	(*pipeblock) = add_pipeblock(shell);
	ft_lstadd_back_pipe(&shell->pipe_head, *pipeblock);
	if (!init_segment(shell, *pipeblock, cur->next))
		return (FAILURE);
	return (SUCCESS);
}
