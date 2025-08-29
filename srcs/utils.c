/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:42:36 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/08/29 15:47:35 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_banner(void)
{
	char	*line;
	int	fd;

	fd = open("banner.txt", O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	line = get_next_line(fd);
	while (42)
	{
		if (line == NULL)
			break  ;
		ft_trimchar(line, '\n');
		ft_printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (line)
		free(line);
}

static void	increment_elements(t_arr *elem, size_t	type)
{
	if (type == 0)
	{
		elem->qcount++;
		elem->w_countin_q++;
	}
	if (type == 1)
		elem->w_countin_q = 1;
	if (type == 2)
	{
		elem->qcount = 0;
		elem->w_countin_q = 0;
	}
}

static char	*joinlines(t_arr *elem, char *array, char *array2, size_t type)
{
	char	*newarray;
	t_arena	*arena;

	if (type == 0)
	{
		elem->line = ft_strjoin(array2, ' ');
		newarray = ft_strjoin(elem->line, array);
		free(elem.line);
		increment_elements(elem, 1);
		return (newarray);
	}
	if (type == 1)
	{
		elem.line = ft_strjoin(array2, ' ');
		newarray = arena_strjoin(arena, elem.line, array);
		free(elem.line);
		increment_elements(elem, 2);
		return (newarray);
	}
}

char	**loop_token_array(char	**tok_arr, t_arr *elem, size_t wc)
{
	char	**array;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	array = arena_alloc(arena, (sizeof(char *) * wordcount));
	if (!array)
		return (NULL);
	while (tok_arr[i])
	{
		j = 0;
		while (tok_arr[i][j])
		{
			if (tok_arr[i][j] == ''' || '"')
				increment_elements(&elem, 0);
			if (tok_arr[i][j] == '\0'
				&& elem.qcount == 1 && elem.w_countin_q == 2)
				tok_arr[i] = joinlines(&elem, tok_arr[i], tok_arr[i - 1], 0);
			else if (tok_arr[i][j] == '\0' && elem.qcount == 2
				&& elem.w_countin_q == 2)
				array[i] = joinlines(&elem, tok_arr[i], tok_arr[i - 1], 1);
			else if (tok_arr[i][j] == '\0' && elem.qcount == 0)
			{
				array[i] = arena_alloc(arena, sizeof(char) * ft_strlen(tok_arr[i]));
				if (!array[i])
				return (NULL);
			}
			j++;
		}
		if (elem.qcount == 1)
			elem.w_countin_q++;
		i++;
	}
	return (array);
}
