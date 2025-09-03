
#include "minishell.h"

static t_env	*env_new_pair(const char *key, const char *val)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(*env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	env->val = NULL;
	if (val)
		env->val = ft_strdup(val);
	env->next = NULL;
	if (!env->key || (val && !env->val))
	{
		free(env->key);
		free(env->val);
		free(env);
		return (NULL);
	}
	return (env);
}

static int	split_keyval(const char *str, char **key, char **val)
{
	int	i;

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
		*val = (char *)(str + i + 1);
	return (SUCCESS);
}

t_env	*env_from_environ(char **envp)
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
		if (!split_keyval(*envp, &key, &val))
			return (env_free(head), NULL);
		node = env_new_pair(key, val);
		free(key);
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
