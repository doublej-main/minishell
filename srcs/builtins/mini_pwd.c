/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:41:06 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/02 17:41:08 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_pwd(void)
{
	char	buf[4096];
	char	*cwd;

	cwd = getcwd(buf, sizeof(buf));
	if (!cwd)
		return (perror("pwd"), EXIT_FAILURE);
	ft_putstr(cwd);
	ft_putchar('\n');
	return (EXIT_SUCCESS);
}
