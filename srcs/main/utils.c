/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:45:53 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/02 17:45:55 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_banner(void)
{
	char	*line;
	int		fd;

	fd = open("banner.txt", O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	line = get_next_line(fd);
	while (42)
	{
		if (line == NULL)
			break ;
		ft_trimchar(line, '\n');
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (line)
		free(line);
}
