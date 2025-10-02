/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:40:06 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/02 17:40:10 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_cd(char **argv, t_shell *shell)
{
	char	buf[4096];
	char	*dir;
	char	*old;

	if (argv[1] && argv[2])
		return (ft_putstr_fd("cd : too many arguments\n", 2), EXIT_FAILURE);
	dir = argv[1];
	if (!dir || dir[0] == '~')
	{
		dir = env_get(shell->env, "HOME");
		if (!dir || !*dir)
			return (ft_putstr_fd("cd: HOME not set\n", 2), EXIT_FAILURE);
	}
	old = getcwd(buf, sizeof(buf));
	if (chdir(dir) < 0)
		return (ft_putstr_fd("cd error\n", 2), EXIT_FAILURE);
	if (old)
		set_new_pair(&shell->env, "OLDPWD", old);
	if (getcwd(buf, sizeof(buf)))
		set_new_pair(&shell->env, "PWD", buf);
	return (EXIT_SUCCESS);
}
