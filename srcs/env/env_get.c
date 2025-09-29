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
