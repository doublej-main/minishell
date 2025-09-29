/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:43:37 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/09/26 13:11:03 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_prompt(t_arena *arena)
{
	char	*cwd;
	char	*tmp;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = arena_strdup(arena, "?");
	if (!cwd)
		return (NULL);
	tmp = arena_strjoin("minishell ", cwd, arena);
	free(cwd);
	if (!tmp)
		return (NULL);
	prompt = arena_strjoin(tmp, " $> ", arena);
	return (prompt);
}
