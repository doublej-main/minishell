/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:44:41 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/02 17:44:42 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_destroy(t_shell *shell)
{
	env_free(shell->env);
	arena_destroy(shell->arena);
}

void	consume_line(t_shell *shell, char *line)
{
	(void)shell;
	if (line && *line)
		add_history(line);
}
