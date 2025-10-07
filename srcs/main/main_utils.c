/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:44:41 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/06 16:10:26 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}
