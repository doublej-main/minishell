/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:46:39 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/14 14:58:47 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*ft_lstlast_redir(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_redir(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (!lst || !new)
		return ;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_redir(*lst);
	if (last)
		last->next = new;
}

t_redir	*add_redir(t_shell *shell)
{
	t_redir	*temp;

	temp = arena_calloc(shell->arena, sizeof(t_redir));
	if (!temp)
		return (NULL);
	temp->target = NULL;
	temp->next = NULL;
	temp->type = 0;
	temp->quoted = 0;
	temp->hd_tmp = 0;
	return (temp);
}
