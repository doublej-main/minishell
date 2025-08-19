/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:26:53 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/04/24 15:51:19 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		needle;
	int					i;

	if (!s)
		return (0);
	str = s;
	needle = c;
	i = 0;
	while (str && n > 0)
	{
		if (str[i] == needle)
			return ((void *)str);
		str++;
		n--;
	}
	return (0);
}
