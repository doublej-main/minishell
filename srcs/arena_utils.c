/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:10:04 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/08/29 14:20:00 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*arena_alloc(t_arena *arena, size_t needed)
{
	t_arena_block	*temp;
	unsigned char	*ptr;

	temp = arena->head;
	if (needed > (temp->max_size - temp->used_mem))
	{
		temp = arena_add_block(arena, needed);
		if (!temp)
			return (NULL);
	}
	ptr = (unsigned char *)temp->mem + temp->used_mem;
	temp->used_mem += needed;
	return ((void *)ptr);
}
void	*arena_calloc(t_arena *arena, size_t needed)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)arena_alloc(arena, needed);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, needed);
	return ((void *)ptr);
}
char	*arena_strdup(t_arena *arena, const char *str)
{
	size_t	i;
	char	*cpy;

	if (!str)
		return (NULL);
	cpy = arena_alloc(arena, sizeof(char) * ft_strlen(str) + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (str[i])
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*arena_strjoin(char const *s1, char const *s2, t_arena *arena)
{
	char	*cat;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	cat = arena_alloc(arena, ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!cat)
		return (NULL);
	while (s1[i])
	{
		cat[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		cat[i] = s2[j];
		i++;
		j++;
	}
	cat[i] = '\0';
	return (cat);
}
