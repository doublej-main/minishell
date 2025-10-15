/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:41:41 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/15 12:10:08 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get(t_shell *shell, t_env *env, const char *key)
{
	(void)shell;
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
