/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:42:39 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/08 18:41:26 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	has_input_redir(const t_cmd *cmd)
// {
// 	const t_redir	*r;

// 	if (!cmd)
// 		return (0);
// 	r = cmd->in;
// 	while (r)
// 	{
// 		if (r->type == REDIR_IN)
// 			return (1);
// 		r = r->next;
// 	}
// 	return (0);
// }

char	*env_join(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*key_pair;

	tmp = ft_strjoin(s1, s2);
	key_pair = ft_strjoin(tmp, s3);
	free(tmp);
	return (key_pair);
}

char	**env_to_chars(t_env *env)
{
	char	**arr;
	char	*key_pair;
	int		count;
	int		i;

	count = env_count(env);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->val)
			key_pair = env_join(env->key, "=", env->val);
		else
			key_pair = ft_strdup(env->key);
		arr[i++] = key_pair;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

static char	*build_candidate(const char *dir, size_t len, const char *name)
{
	size_t	name_len;
	char	*str;

	name_len = ft_strlen(name);
	if (len == 0)
	{
		str = malloc(name_len + 1);
		if (!str)
			return (NULL);
		ft_memcpy(str, name, name_len);
		str[name_len] = '\0';
		return (str);
	}
	str = malloc(len + 1 + name_len + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, dir, len);
	str[len] = '/';
	ft_memcpy(str + len + 1, name, name_len);
	str[len + 1 + name_len] = '\0';
	return (str);
}

char	*path_search(t_shell *shell, char *name, t_env *env)
{
	const char	*path;
	const char	*start;
	char		*cand;
	size_t		len;

	path = env_get(shell, env, "PATH");
	if (!path || !*path || !name || !*name)
		return (NULL);
	while (69)
	{
		start = path;
		while (*path && *path != ':')
			path++;
		len = (size_t)(path - start);
		cand = build_candidate(start, len, name);
		if (cand && access(cand, X_OK) == 0)
			return (cand);
		free(cand);
		if (!*path)
			break ;
		path++;
	}
	return (NULL);
}
