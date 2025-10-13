/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:41:55 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/13 14:16:09 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*trim_eq(char *key)
{
	int		i;

	if (!key || !*key)
		return (NULL);
	if (!ft_strchr(key, '='))
		return (key);
	i = 0;
	while (key[i] && key[i] != '=')
		i++;
	key[i] = '\0';
	return (key);
}

char	*strip_quotes_env(const char *s)
{
	char	*out;
	int		i;
	int		j;
	char	q;

	out = malloc(ft_strlen(s) + 1);
	if (!out)
		return (NULL);
	i = 0;
	q = 0;
	j = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && q == 0)
			q = s[i];
		else if (q && s[i] == q)
			q = 0;
		else
			out[j++] = s[i];
		i++;
	}
	out[j] = '\0';
	return (out);
}

t_env	*env_find(t_env *env, const char *key)
{
	if (!key || !*key)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	set_new_pair(t_env **env, char *key, const char *val)
{
	t_env	*node;
	char	*new_value;

	if (!env || !key || !is_identifier(key))
		return (FAILURE);
	key = trim_eq(key);
	node = env_find(*env, key);
	if (!node)
	{
		node = env_new_pair(key, val);
		if (!node)
			return (FAILURE);
		node->next = *env;
		*env = node;
	}
	if (val)
	{
		new_value = ft_strdup(val);
		if (!new_value)
			return (FAILURE);
		free(node->val);
		node->val = new_value;
	}
	return (SUCCESS);
}
