/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:07:24 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/09/08 15:36:00 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** Includes
*/
# include "arena.h"
# include "env.h"
# include "libft.h"
# include "prompt.h"
# include "ast.h"
# include "token.h"
# include "signals.h"
# include "utils.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
	t_env						*env;
	int							status;
	t_arena						*arena;
	t_token						*head;
}								t_shell;

/*
** Prototypes
*/
int								shell_init(t_shell *shell, char **environ);
void							shell_loop(t_shell *shell);
void							shell_destroy(t_shell *shell);

#endif
