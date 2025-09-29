/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:43:37 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/09/29 14:21:45 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_prompt(t_arena *arena)
{
	char	*cwd;
	char	*tmp;
	char	*prompt;
	char	*sys;

	sys = getcwd(NULL, 0);
	if (!sys)
		cwd = arena_strdup(arena, "?");
	else
	{
		cwd = arena_strdup(arena, sys);
		free (sys);
	}
	if (!cwd)
		return (NULL);
	tmp = arena_strjoin("minishell ", cwd, arena);
	if (!tmp)
		return (NULL);
	prompt = arena_strjoin(tmp, " $> ", arena);
	return (prompt);
}
