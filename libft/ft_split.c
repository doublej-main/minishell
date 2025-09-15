/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:28:34 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/09/15 13:08:58 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **ptr)
{
	char	**tmp;

	if (!ptr)
		return ;
	tmp = ptr;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(ptr);
}

static int	count_words(const char *str, char c)
{
	size_t	i;
	size_t	trigger;
	size_t	count;

	i = 0;
	trigger = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c && trigger == 0)
		{
			trigger = 1;
			count++;
		}
		else if (str[i] == c)
			trigger = 0;
		i++;
	}
	return (count);
}

static char	**execute_split(char **split, const char *s, char c)
{
	size_t	i;
	size_t	j;
	int		k;

	i = 0;
	j = 0;
	k = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && k < 0)
			k = i;
		else if ((s[i] == c && k != -1) || (i == ft_strlen(s) && k >= 0))
		{
			split[j] = ft_substr(s, k, i - k);
			if (!split[j])
				return (ft_free(split), NULL);
			k = -1;
			j++;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	return (execute_split(split, s, c));
}
