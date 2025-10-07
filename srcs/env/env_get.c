/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:41:41 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/02 17:41:43 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get(t_env *env, const char *key)
{
	while (env)
	{
		if (env->key && key && !ft_strncmp(env->key, key, ft_strlen(key)))
			return (env->val);
		env = env->next;
	}
	return (NULL);
}
