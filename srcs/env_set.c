#include "minishell.h"

t_env	*env_find(t_env *env, const char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	set_new_pair(t_env *env, const char *key, const char *val)
{
	t_env	*node;
	char	*new_value;

	if (!env || !key || !is_identifier(key))
		return (FAILURE);
	node = env_find(env, key);
	if (!node)
	{
		node = env_new_pair(key, val);
		if (!node)
			return (FAILURE);
		node->next = env;
		env = node;
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
