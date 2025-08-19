/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:35:48 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/07/29 15:47:46 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_free(char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}

char	*extract_line(char *ptr)
{
	char	*split;
	char	*line;
	int		len_to_copy;

	if (!ptr)
		return (NULL);
	split = ft_strchr(ptr, '\n');
	if (split)
		len_to_copy = split - ptr + 1;
	else
		len_to_copy = ft_strlen(ptr);
	line = ft_substr(ptr, 0, len_to_copy);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1)
		joined = ft_strjoin("", s2);
	else
		joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

char	*trim_stash(char **stash)
{
	char	*split;
	char	*tail;

	if (!*stash)
		return (NULL);
	split = ft_strchr(*stash, '\n');
	if (split && *(split + 1))
	{
		tail = ft_strdup(split + 1);
		if (!tail)
			return (gnl_free(stash), NULL);
	}
	else
		tail = NULL;
	gnl_free(stash);
	return (tail);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash[fd], '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (gnl_free(&stash[fd]), NULL);
		buffer[bytes_read] = '\0';
		stash[fd] = ft_strjoin_free(stash[fd], buffer);
		if (!stash[fd])
			return (NULL);
	}
	if ((bytes_read == 0 && stash[fd] == NULL) || *stash[fd] == '\0')
		return (gnl_free(&stash[fd]), NULL);
	line = extract_line(stash[fd]);
	if (!line)
		return (gnl_free(&stash[fd]), NULL);
	stash[fd] = trim_stash(&stash[fd]);
	return (line);
}
