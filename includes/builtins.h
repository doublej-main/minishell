/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:36:21 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/02 17:36:24 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

struct					s_shell;
typedef struct s_shell	t_shell;
/*
** dispatch.c
*/
int						is_any_builtin(const char *name);
int						is_parent_builtin(const char *name);
int						run_any_builtin(const char *name, char **argv,
							t_shell *shell);
int						run_parent_builtin_cmd(const char *name, char **argv,
							t_shell *shell);
/*
** mini_cd.c
*/
int						mini_cd(char **argv, t_shell *shell);
/*
** mini_echo.c
*/
int						mini_echo(char **argv, int i, t_shell *shell);
/*
** mini_export.c
*/
int						mini_export(char **argv, t_shell *shell);
int						is_identifier(const char *str);
/*
** mini_unset.c
*/
int						mini_unset(char **argv, t_shell *shell);
/*
** mini_env
*/
int						mini_env(t_shell *shell);
/*
** mini_exit.c
*/
int						mini_exit(char **argv, t_shell *shell);
/*
** mini_pwd.c
*/
int						mini_pwd(void);

#endif
