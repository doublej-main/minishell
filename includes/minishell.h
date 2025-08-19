/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:07:24 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/08/19 15:32:28 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** Includes
*/
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "signals.h"
# include "env.h"
# include "prompt.h"
# include "libft.h"

/*
** Macros
*/
# define SUCCESS 1
# define FAILURE 0

/*
** Variables and structs
*/
extern volatile sig_atomic_t	g_sig;

typedef struct s_shell
{
	t_env	*env;
	int	status;
}	t_shell;

/*
** Prototypes
*/
void	shell_init(t_shell *shell, char **environ);
void	shell_loop(t_shell *shell);
void	shell_destroy(t_shell *shell);

#endif