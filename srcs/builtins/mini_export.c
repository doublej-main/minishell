#include "minishell.h"

int	is_identifier(const char *str)
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

int	mini_export(char **argv, t_shell *shell)
{
	int		i;
	char	*equal_sign;
	char	*key;
	char	*val;

	if (!argv[1])
		return (print_sorted_env(shell->env));
	i = 1;
	while (argv[i])
	{
		equal_sign = ft_strchr(argv[i], '=');
		if (!is_identifier(argv[i]))
			return (ft_putstr_fd("export: not an identifier\n", 2), FAILURE);
		else if (equal_sign && equal_sign[1] != '\0')
		{
			split_keyval(argv[i++], &key, &val);
			set_new_pair(&shell->env, key, val);
		}
		else if (equal_sign)
			set_new_pair(&shell->env, argv[i++], "");
		else
			set_new_pair(&shell->env, argv[i++], NULL);
	}
	return (EXIT_SUCCESS);
}
