/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:39:13 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/09/11 11:46:28 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include "../libft/libft.h"
# include <stddef.h>

# define INIT_FAIL -1
# define SUCCESS 1
# define FAILURE 0

typedef struct s_arena_block
{
	struct s_arena_block	*next;
	size_t					max_size;
	size_t					used_mem;
	unsigned char			*mem;
}							t_arena_block;

typedef struct s_arena
{
	t_arena_block			*head;
	size_t					block_size;
}							t_arena;

/**
 * Prototypes
 */
int				arena_init(t_arena *arena, size_t block_size);
void			arena_destroy(t_arena *arena);
void			arena_reset(t_arena *arena);
t_arena_block	*arena_add_block(t_arena *arena, size_t needed);
void			*arena_alloc(t_arena *arena, size_t needed);
void			*arena_calloc(t_arena *arena, size_t needed);
char			*arena_strdup(t_arena *arena, const char *str);
char			*arena_strjoin(char const *s1, char const *s2, t_arena *arena);
char			*arena_substr(char const *s, size_t start, size_t len,
					t_arena *arena);

#endif
