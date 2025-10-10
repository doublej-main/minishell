/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:41:41 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/10 16:55:30 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get(t_shell *shell, t_env *env, const char *key)
{
	char	*itoa;
	char	*val;

	itoa = NULL;
	val = NULL;
	if (!ft_strcmp(key, "?"))
	{
		itoa = ft_itoa(shell->status);
		val = arena_strdup(shell->arena, itoa);
		free(itoa);
		return (val);
	}
	while (env)
	{
		if (env->key && key && !ft_strncmp(env->key, key, ft_strlen(key))
			&& ft_strcmp(key, "") != 0)
			return (env->val);
		else if (ft_strcmp(key, "") == 0)
			return ("");
		env = env->next;
	}
	return (NULL);
}
