/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:40:35 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/10 14:02:59 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned char	exit_code_from_str(const char *str)
{
	int				sign;
	unsigned char	code;

	sign = 1;
	code = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		code = (code * 10 + (*str - '0')) % 256;
		str++;
	}
	if (sign < 0)
		code = (256 - code) % 256;
	return (code);
}

int	mini_exit(char **argv, t_shell *shell)
{
	unsigned char	exit_code;

	exit_code = 0;
	if (!argv[1])
	{
		shell_destroy(shell);
		exit(shell->status);
	}
	argv[1] = strip_quotes(shell->arena, argv[1]);
	if (!ft_isnum(argv[1]))
	{
		ft_putstr_fd("exit: numeric arg required\n", 2);
		shell_destroy(shell);
		exit(2);
	}
	if (argv[1] && argv[2])
	{
		perror("exit: too many args\n");
		return (EXIT_FAILURE);
	}
	exit_code = exit_code_from_str(argv[1]);
	shell_destroy(shell);
	exit(exit_code);
}
