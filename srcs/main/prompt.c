/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:44:59 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/02 17:45:01 by vahdekiv         ###   ########.fr       */
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
