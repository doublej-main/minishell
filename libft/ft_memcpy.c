/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:33:55 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/04/24 11:10:52 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_array;
	const unsigned char	*src_array;
	size_t				i;

	dest_array = dest;
	src_array = src;
	i = 0;
	while (i < n)
	{
		dest_array[i] = src_array[i];
		i++;
	}
	return (dest);
}
