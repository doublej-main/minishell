/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:44:41 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/15 12:11:46 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_for_shell_status(t_shell *shell, char *str)
{
	char	*itoa;
	char	*val;

	if (!str || !*str)
		return (NULL);
	itoa = NULL;
	val = NULL;
	if (!ft_strcmp(str, "$?"))
	{
		itoa = ft_itoa(shell->status);
		val = arena_strdup(shell->arena, itoa);
		free(itoa);
		return (val);
	}
	return (NULL);
}

void	shell_destroy(t_shell *shell)
{
	env_free(shell->env);
	arena_destroy(shell->arena);
	close(shell->fd_in);
}

void	consume_line(t_shell *shell, char *line)
{
	(void)shell;
	if (line && *line)
		add_history(line);
	shell->empty = 0;
}
