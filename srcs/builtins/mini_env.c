#include "minishell.h"

int	mini_env(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (tmp->val)
		{
			printf("%s = %s\n", tmp->key, tmp->val);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
