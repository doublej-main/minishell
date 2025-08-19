/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:53:48 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/07/29 15:51:57 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trimchar(char *line, char c)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != c)
		len++;
	line[len] = '\0';
	return (line);
}
