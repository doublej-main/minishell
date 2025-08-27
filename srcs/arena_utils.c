/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:10:04 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/08/27 15:39:32 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	*arena_alloc(t_arena *arena, size_t needed)
{
	t_arena_block	*temp;
	void			*ptr;

	temp = arena->head;
	if (needed > (temp->max_size - temp->used_mem))
	{
		ptr = arena_add_block(arena, needed);
		temp->used_mem += needed;
		return (ptr);
	}
	ptr = temp->mem + temp->used_mem;
	return (ptr);
}
void	*arena_calloc(t_arena *arena, size_t needed)
{
	t_arena_block	*temp;
	void			*ptr;

	temp = arena->head;
	if (needed > (temp->max_size - temp->used_mem))
	{
		ptr = arena_add_block(arena, needed);
		ft_bzero(temp->mem, needed);
		temp->used_mem += needed;
		return (ptr);
	}
	ft_bzero(temp->mem + temp->used_mem, needed);
	ptr = temp->mem + temp->used_mem;
	return (ptr);
}
char	*arena_strdup(t_arena *arena, const char *str)
{

}
