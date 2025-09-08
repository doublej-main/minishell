
#include "minishell.h"

static void	increment_elements(t_arr *elem)
{
	elem->qcount++;
	elem->w_countin_q++;
}

static char	*joinlines(t_arr *elem, char *array, char *array2, t_arena *arena)
{
	char	*newarray;

	elem->line = arena_strjoin(array2, " ", arena);
	newarray = arena_strjoin(elem->line, array, arena);
	return (newarray);
}

static char	*build_array(char *token, char *token2, t_arr *elem, t_arena *arena)
{
	char	*token_array;

	token_array = NULL;
	if (elem->qcount == 1 && elem->w_countin_q == 2)
	{
		token_array = joinlines(elem, token, token2, arena);
		elem->w_countin_q = 1;
		if (!token_array)
			return (NULL);
	}
	else if (elem->qcount == 0 || elem->qcount == 2)
	{
		token_array = arena_alloc(arena, sizeof(char) * ft_strlen(token));
		if (!token_array)
			return (NULL);
	}
	else if (elem->qcount == 2 && elem->w_countin_q == 2)
	{
		token_array = joinlines(elem, token, token2, arena);
		elem->qcount = 0;
		elem->w_countin_q = 0;
		if (!token_array)
			return (NULL);
	}
	return (token_array);
}

char	**loop_token_array(char	**token, t_arr *elem, t_arena *arena, size_t wc)
{
	char	**array;
	size_t	i;
	size_t	j;

	i = 0;
	array = arena_alloc(arena, (sizeof(char *) * wc));
	if (!array)
		return (NULL);
	while (token[i])
	{
		j = 0;
		while (token[i][j])
		{
			if (token[i][j] == '\'' || token[i][j] == '\"')
				increment_elements(elem);
			if (token[i][j++] == '\0' && token[i - 1])
				array[i - 1] = build_array(token[i], token[i - 1], elem, arena);
		}
		if (elem->qcount == 1)
			elem->w_countin_q++;
		i++;
	}
	return (array);
}
