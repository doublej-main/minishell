/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_cmd_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:46:23 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/15 13:52:44 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argv_builder(t_pl *pb, t_shell *shell, t_token *curr, int i)
{
	char	*temp;

	if (i < pb->cmd->ac)
	{
		temp = def_argv(shell->arena, curr->value);
		check_for_env(shell, &temp);
		if (!temp)
			return (i);
		pb->cmd->argv[i] = strip_quotes(shell->arena, temp);
		i++;
	}
	return (i);
}

int	only_dollars(char *line)
{
	size_t	i;

	i = 0;
	if (line[i] == '"' && line[ft_strlen(line) - 1] == '"')
		i++;
	while (i < ft_strlen(line) - 1)
	{
		if (line[i] != '$' && !isdel(line[i]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
