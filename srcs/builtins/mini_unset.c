#include "minishell.h"

int	mini_unset(char **argv, t_shell *shell)
{
	int	i;

	i = 1;
	
	while (argv[i])
	{
		if (!is_identifier(argv[i]))
		{
			ft_putstr_fd("unset : not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		else
		{
			if (env_unset(shell->env, argv[i]) > 0)
				return (ft_putstr_fd("Variable was not set\n", 1), SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
