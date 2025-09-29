/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:42:36 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/09/25 12:48:59 by jjaaskel         ###   ########.fr       */
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
		ft_printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (line)
		free(line);
}
