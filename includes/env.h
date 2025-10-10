/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:36:33 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/10 10:31:29 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/*
** Variables and structs
*/
typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;

}					t_env;
/*
** env.c
*/
t_env				*env_from_environ(t_shell *shell, char **envp);
void				env_free(t_env *env);
t_env				*env_new_pair(const char *key, const char *val);
int					split_keyval(t_shell *shell, const char *str, char **key,
						char **val);
/*
** builtin helpers
*/
char				*env_get(t_shell *shell, t_env *env, const char *key);
int					is_identifier(const char *str);
int					print_sorted_env(t_env *env);
int					set_new_pair(t_env **env, char *key, const char *val);
int					env_unset(t_env **env, const char *key);
int					env_to_array(t_env *env, t_env **arr, int count);
int					env_count(t_env *env);
t_env				*env_find(t_env *env, const char *key);
char				*strip_quotes_env(const char *s);

#endif
