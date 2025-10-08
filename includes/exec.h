/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:36:42 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/08 14:31:54 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

struct					s_shell;
typedef struct s_shell	t_shell;

struct					s_pl;
typedef struct s_pl		t_pl;

struct					s_cmd;
typedef struct s_cmd	t_cmd;

struct					s_env;
typedef struct s_env	t_env;

typedef struct s_fd
{
	int					count;
	int					fd[2];
	int					prev_in;
	int					out_fd;
}						t_fd;

int						execute_pipeline(t_pl *pl, t_shell *shell);
void					exec_external_or_builtin(const t_cmd *cmd,
							t_shell *shell);
int						run_pipeline(t_pl *pl, t_shell *shell);
char					**env_to_chars(t_env *env);
char					*env_join(const char *s1, const char *s2,
							const char *s3);
char					*path_search(t_shell *shell, char *name, t_env *env);
int						run_single(t_cmd *cmd, t_shell *shell);
int						io_apply_redirs(const t_cmd *cmd);
void					io_restore_std(int save_in, int save_out);
int						open_out(const t_redir *r);
void					even_earlier_exit(t_shell *shell, int status);

#endif
