/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:10:04 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/09/19 12:22:50 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	*arena_alloc(t_arena *arena, size_t needed)
// {
// 	t_arena_block	*temp;
// 	unsigned char	*ptr;

// 	temp = arena->head;
// 	if (needed > (temp->max_size - temp->used_mem))
// 	{
// 		temp = arena_add_block(arena, needed);
// 		if (!temp)
// 			return (NULL);
// 	}
// 	ptr = (unsigned char *)temp->mem + temp->used_mem;
// 	temp->used_mem += needed;
// 	return ((void *)ptr);
// }

void	*arena_alloc(t_arena *arena, size_t needed)
{
	unsigned char	*ptr;

	if (needed > (arena->head->max_size - arena->head->used_mem))
	{
		arena_add_block(arena, needed);
		if (!arena->head || !arena->head->mem)
			return (NULL);
	}
	ptr = (unsigned char *)arena->head->mem + arena->head->used_mem;
	arena->head->used_mem += needed;
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

char	*arena_substr(char const *s, size_t start, size_t len, t_arena *arena)
{
	char	*sub;
	size_t	i;
	size_t	j;
	size_t	length;

	if (!s)
		return (NULL);
	i = start;
	j = 0;
	length = ft_strlen(s);
	if (start >= length)
		return (ft_calloc(1, 1));
	if (len > length - start)
		len = length - start;
	sub = arena_alloc(arena, sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (s[i] && j < len)
	{
		sub[j] = s[i];
		i++;
		j++;
	}
	sub[j] = '\0';
	return (sub);
}
