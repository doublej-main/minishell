/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:51:52 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/08/28 15:28:19 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

t_arena_block	*arena_new_block(size_t block_size)
{
	t_arena_block	*new_block;

	new_block = malloc(sizeof(*new_block));
	if (!new_block)
		return (NULL);
	new_block->mem = malloc(block_size * sizeof(unsigned char));
	if (!new_block->mem)
		return (free(new_block), NULL);
	new_block->next = NULL;
	new_block->max_size = block_size;
	new_block->used_mem = 0;
	return (new_block);
}

t_arena_block	*arena_add_block(t_arena *arena, size_t needed)
{
	size_t			max;
	t_arena_block	*new_block;

	if (needed > arena->block_size)
		max = arena->block_size + (needed - arena->block_size);
	else
		max = arena->block_size;
	new_block = arena_new_block(max);
	if (!new_block)
		return (NULL);
	new_block->next = arena->head;
	arena->head = new_block;
	return (new_block);
}

int	arena_init(t_arena *arena, size_t block_size)
{
	t_arena_block	*block;

	if (!arena || block_size == 0)
		return (INIT_FAIL);
	block = arena_new_block(block_size);
	if (!block)
		return (INIT_FAIL);
	arena->head = block;
	arena->block_size = block_size;
	return (SUCCESS);
}

void	arena_reset(t_arena *arena)
{
	t_arena_block	*keep;
	t_arena_block	*tmp;
	t_arena_block	*next;

	if (!arena || !arena->head)
		return ;
	keep = arena->head;
	tmp = keep->next;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->mem);
		free(tmp);
		tmp = next;
	}
	keep->used_mem = 0;
	keep->next = NULL;
}

void	arena_destroy(t_arena *arena)
{
	t_arena_block	*tmp;
	t_arena_block	*next;

	if (!arena)
		return ;
	tmp = arena->head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->mem);
		free(tmp);
		tmp = next;
	}
	arena->head = NULL;
}
