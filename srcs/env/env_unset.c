#include "minishell.h"

int	env_unset(t_env **env, const char *key)
{
	t_env	*cur;
	t_env	*prev;

	if (!env || !*env || !key)
		return (FAILURE);
	prev = NULL;
	cur = *env;
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->val);
			free(cur);
			return (EXIT_SUCCESS);
		}
		prev = cur;
		cur = cur->next;
	}
	return (SUCCESS);
}
