/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:41:30 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/08 15:08:02 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_node(t_env *env)
{
	if (env->key)
		free(env->key);
	if (env->val)
		free(env->val);
	free(env);
}

t_env	*env_new_pair(const char *key, const char *val)
{
	t_env	*env;
	char	*equal;

	equal = NULL;
	env = (t_env *)malloc(sizeof(*env));
	if (!env)
		return (NULL);
	equal = ft_strchr(key, '=');
	if (equal)
		env->key = ft_substr(key, 0, equal - key);
	else
		env->key = ft_strdup(key);
	env->val = NULL;
	if (val)
		env->val = ft_strdup(val);
	env->next = NULL;
	if (!env->key || (val && !env->val))
	{
		free_node(env);
		return (NULL);
	}
	return (env);
}

int	split_keyval(t_shell *shell, const char *str, char **key, char **val)
{
	int	i;

	(void)shell;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	*key = NULL;
	*val = NULL;
	*key = malloc(i + 1);
	if (!*key)
		return (FAILURE);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		(*key)[i] = str[i];
		i++;
	}
	(*key)[i] = '\0';
	if (str[i] == '=')
	{
		*val = (char *)(str + i + 1);
		*val = strip_quotes_env(*val);
	}
	return (SUCCESS);
}

t_env	*env_from_environ(t_shell *shell, char **envp)
{
	t_env	*head;
	t_env	*tail;
	char	*key;
	char	*val;
	t_env	*node;

	head = NULL;
	tail = NULL;
	while (envp && *envp)
	{
		if (!split_keyval(shell, *envp, &key, &val))
			return (env_free(head), NULL);
		node = env_new_pair(key, val);
		free(key);
		free(val);
		if (!node)
			return (env_free(head), NULL);
		if (!head)
			head = node;
		else
			tail->next = node;
		tail = node;
		envp++;
	}
	return (head);
}

void	env_free(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->val);
		free(env);
		env = next;
	}
}
