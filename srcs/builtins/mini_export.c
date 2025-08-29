#include "minishell.h"

static int	is_identifier(const char *str)
{
	int	i;

	if (!str || !(ft_isalpha(*str) || *str == '_'))
		return (FAILURE);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	mini_export(char *argv, t_shell *shell)
{
	int i;
	char *equal_sign;

	if (!argv[1])
		return (print_sorted_env(shell->env)); //TODO
	i = 0;
	while (argv[i])
	{
		equal_sign = ft_strchr(argv[i], '=');
		if (!is_identifier(argv[i]))
			return (perror("export: not a valid identifier\n"), FAILURE);
		else if (equal_sign)
			set_env_pair(shell, argv[i], NULL);
		else
			set_env_pair(shell, argv[i], "");
		i++;	
	}
	return (EXIT_SUCCESS);
}
