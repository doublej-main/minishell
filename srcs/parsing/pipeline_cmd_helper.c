/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_cmd_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:46:23 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/02 17:46:25 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argv_builder(t_pl *pb, t_shell *shell, t_token *curr, int i)
{
	if (i < pb->cmd->ac)
	{
		pb->cmd->argv[i] = def_argv(shell->arena, curr->value);
		i++;
	}
	return (i);
}
