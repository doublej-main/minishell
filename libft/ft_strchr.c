/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:54:26 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/06/23 15:29:35 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	needle;
	int				i;

	if (!s)
		return (0);
	needle = c;
	i = 0;
	while (*s)
	{
		if (s[i] == needle)
			return ((char *)s);
		s++;
	}
	if (needle == 0)
		return ((char *)s);
	return (0);
}
