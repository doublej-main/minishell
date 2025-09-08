#include "minishell.h"

int	mini_unset(char **argv, t_shell *shell)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_identifier(argv[i]))
		{
			perror("unset : not a valid identifier\n");
			return (EXIT_FAILURE);
		}
		else
			env_unset(shell->env, argv[i]);//TODO
		i++;
	}
	return (EXIT_SUCCESS);
}
