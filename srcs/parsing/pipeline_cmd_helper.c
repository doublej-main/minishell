/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_cmd_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:46:23 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/10 17:26:51 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argv_builder(t_pl *pb, t_shell *shell, t_token *curr, int i)
{
	char	*temp;

	if (i < pb->cmd->ac)
	{
		temp = def_argv(shell->arena, curr->value);
		pb->cmd->argv[i] = strip_quotes(shell->arena, temp);
		i++;
	}
	return (i);
}
