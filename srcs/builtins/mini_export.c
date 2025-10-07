/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:40:58 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/07 16:51:51 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_keypair(char *key, char *val)
{
	if (key)
		free(key);
	if (val)
		free(val);
}

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
			return (ft_putstr_fd("export: not an id\n", 2), EXIT_FAILURE);
		else if (equal_sign && equal_sign[1] != '\0')
		{
			split_keyval(shell, argv[i++], &key, &val);
			set_new_pair(&shell->env, key, val);
			free_keypair(key, val);
		}
		else if (equal_sign)
			set_new_pair(&shell->env, argv[i++], "");
		else
			set_new_pair(&shell->env, argv[i++], NULL);
	}
	return (EXIT_SUCCESS);
}
