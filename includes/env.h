/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:19:19 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/08/19 13:49:44 by jjaaskel         ###   ########.fr       */
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

t_env				*env_from_environ(char **envp);
void				env_free(t_env *env);

#endif