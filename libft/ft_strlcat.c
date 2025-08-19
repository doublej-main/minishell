/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:22:18 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/04/24 17:04:04 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;
	size_t	value;

	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	value = destlen + srclen;
	i = 0;
	if (!dest || !src)
		return (0);
	if (size < destlen)
		return (size + srclen);
	if (size > 0 && size > destlen + 1)
	{
		while (src[i] && destlen <= size - 2)
		{
			dest[destlen] = src[i];
			i++;
			destlen++;
		}
	}
	dest[destlen] = '\0';
	return (value);
}
